
// ===== Imports =====
use anyhow::Result;
use crate::cartridge::cart_type::{CartridgeType, get_cartridge_type};
// ===================

pub struct CartridgeHeader {
  pub title: String,
  pub cart_type: CartridgeType,
  pub sram: bool,
  pub battery: bool,
  pub rtc: bool, // timer
  pub rom_size: (usize, usize), // (No. of ROM Banks, ROM size)
  pub ram_size: (usize, usize), // (No. of RAM Banks, RAM size)
}

impl CartridgeHeader {
  pub fn from(byts: &[u8]) -> Result<Self> {
    let title = String::from_utf8_lossy(&byts[0x134..0x143]).to_string();
    let (cart_type, sram, battery, rtc) = get_cartridge_type(byts[0x147])?;
    let rom_size = get_rom_details(byts[0x148]);
    let ram_size = get_ram_details(byts[0x149]);
    
    Ok(Self { title, cart_type, sram, battery, rtc, rom_size, ram_size })
  }
}

pub const ROM_BANK_SIZE: usize = 16 * 1024;
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

pub const RAM_BANK_SIZE: usize = 8 * 1024;
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