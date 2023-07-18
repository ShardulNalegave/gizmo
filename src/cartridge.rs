
pub mod cart_type;
pub mod rom;
pub mod mbc1;
pub mod mbc2;
pub mod mbc3;
pub mod mbc5;

// ===== Imports =====
use crate::cartridge::cart_type::{CartridgeType, get_cartridge_type};
use crate::cartridge::mbc1::MBC1;
use crate::cartridge::mbc2::MBC2;
use crate::cartridge::mbc3::MBC3;
use crate::cartridge::mbc5::MBC5;
use crate::cartridge::rom::ROM;
// ===================

pub trait Cartridge {
  fn cartridge_header(&self) -> &CartridgeHeader;
  fn get(&self, pos: u16) -> u8;
  fn set(&mut self, pos: u16, val: u8);
}

pub enum DestinationCode {
  Japanese = 0,
  NonJapanese = 1,
}

pub struct CartridgeHeader {
  pub title: String,
  pub destination_code: DestinationCode,
  pub cart_type: CartridgeType,
  pub sram: bool,
  pub battery: bool,
  pub rtc: bool,
  pub rom: (usize, usize), // (No. of ROM Banks, ROM Size)
  pub ram: (usize, usize), // (No. of RAM Banks, RAM Size)
}

impl From<&[u8]> for CartridgeHeader {
  fn from(byts: &[u8]) -> Self {
    let (cart_type, sram, battery, rtc) = get_cartridge_type(byts[0x0147]);
    let title = String::from_utf8(byts[0x0134..=0x0142].to_vec()).expect("Couldn't parse ROM Title");

    let destination_code;
    match byts[0x014A] {
      0 => destination_code = DestinationCode::Japanese,
      1 => destination_code = DestinationCode::NonJapanese,
      _ => panic!("Invalid Destination Code"),
    }

    let rom = get_rom_details(byts[0x0148]);
    let ram = get_ram_details(byts[0x0149]);

    Self {
      title,
      destination_code,
      cart_type, sram, battery, rtc,
      rom, ram,
    }
  }
}

pub fn new_cartridge(byts: Vec<u8>) -> Box<dyn Cartridge> {
  let (cart_type, _, _, _) = get_cartridge_type(byts[0x0147]);
  Box::new(match cart_type {
    CartridgeType::ROM => ROM::new(byts),
    CartridgeType::MBC1 => MBC1::new(byts),
    CartridgeType::MBC2 => MBC2::new(byts),
    CartridgeType::MBC3 => MBC3::new(byts),
    CartridgeType::MBC5 => MBC5::new(byts),
  })
}

const ROM_BANK_SIZE: usize = 16 * 1024;
fn get_rom_details(code: u8) -> (usize, usize) { // (No. of ROM Banks, ROM Size)
  match code {
    0x0000 => (2, 2 * ROM_BANK_SIZE),
    0x0001 => (4, 4 * ROM_BANK_SIZE),
    0x0002 => (8, 8 * ROM_BANK_SIZE),
    0x0003 => (16, 16 * ROM_BANK_SIZE),
    0x0004 => (32, 32 * ROM_BANK_SIZE),
    0x0005 => (64, 64 * ROM_BANK_SIZE),
    0x0006 => (128, 128 * ROM_BANK_SIZE),
    0x0007 => (256, 256 * ROM_BANK_SIZE),
    0x0008 => (512, 512 * ROM_BANK_SIZE),
    _ => panic!("Invalid ROM-size value"),
  }
}

const RAM_BANK_SIZE: usize = 8 * 1024;
fn get_ram_details(code: u8) -> (usize, usize) { // (No. of RAM Banks, RAM Size)
  match code {
    0x0000 => (0, 0),
    0x0002 => (1, RAM_BANK_SIZE),
    0x0003 => (4, 4 * RAM_BANK_SIZE),
    0x0004 => (16, 16 * RAM_BANK_SIZE),
    0x0005 => (8, 8 * RAM_BANK_SIZE),
    _ => panic!("Invalid RAM-size value"),
  }
}