
// ===== Imports =====
use crate::cartridge::{Cartridge, CartridgeHeader};
// ===================

pub struct MBC1 {
  header: CartridgeHeader,
  byts: Vec<u8>,
}

impl MBC1 {
  pub fn new(byts: Vec<u8>) -> Self {
    let header = CartridgeHeader::from(&byts);
    Self { header, byts }
  }
}

impl Cartridge for MBC1 {
  fn cartridge_header(&self) -> &CartridgeHeader {
    &self.header
  }

  fn get(&self, pos: u16) -> u8 {
    todo!()
  }

  fn set(&mut self, pos: u16, val: u8) {
    todo!()
  }
}