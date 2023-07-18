
// ===== Imports =====
use crate::cartridge::{Cartridge, CartridgeHeader};
// ===================

pub struct ROM {
  header: CartridgeHeader,
  byts: Vec<u8>,
}

impl ROM {
  pub fn new(byts: Vec<u8>) -> Self {
    let header = CartridgeHeader::from(&byts);

    if header.rom.0 != 2 {
      panic!("Invalid Number of ROM Banks for ROM-Only Cartridge")
    }

    Self { header, byts }
  }
}

impl Cartridge for ROM {
  fn cartridge_header(&self) -> &CartridgeHeader {
    &self.header
  }

  fn get(&self, pos: u16) -> u8 {
    if (0x0000..0x8000).contains(&pos) {
      self.byts[pos]
    } else {
      panic!("Address out-of-bounds")
    }
  }

  fn set(&mut self, pos: u16, val: u8) {
    self.byts[pos] = val;
  }
}