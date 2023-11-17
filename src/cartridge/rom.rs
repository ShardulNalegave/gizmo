
// ===== Imports =====
use std::ops::Index;
use crate::cartridge::{
  Cartridge,
  header::CartridgeHeader,
};
// ===================

pub struct ROM {
  header: CartridgeHeader,
  byts: Vec<u8>,
}

impl ROM {
  pub fn new(header: CartridgeHeader, byts: &[u8]) -> Self {
    Self { header, byts: byts.to_vec() }
  }
}

impl Cartridge for ROM {
  fn get_header(&self) -> &CartridgeHeader {
    &self.header
  }

  fn set(&mut self, index: u16, byt: u8) {
    self.byts[index as usize] = byt;
  }
}

impl Index<u16> for ROM {
  type Output = u8;
  fn index(&self, index: u16) -> &Self::Output {
    &self.byts[index as usize]
  }
}