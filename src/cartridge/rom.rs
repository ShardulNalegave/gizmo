
// ===== Imports =====
use std::ops::{Index, IndexMut};
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
}

impl Index<u16> for ROM {
  type Output = u8;
  fn index(&self, index: u16) -> &Self::Output {
    &self.byts[index as usize]
  }
}

impl IndexMut<u16> for ROM {
  fn index_mut(&mut self, index: u16) -> &mut Self::Output {
    &mut self.byts[index as usize]
  }
}