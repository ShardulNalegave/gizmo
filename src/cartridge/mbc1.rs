
// ===== Imports =====
use std::ops::Index;
use crate::cartridge::{
  Cartridge,
  RAM_BANK_SIZE, ROM_BANK_SIZE,
  header::CartridgeHeader,
};
// ===================

pub struct MBC1 {
  header: CartridgeHeader,
  rambank_enabled: bool,
  rambank_selected: u8,
  rambanks: Vec<[u8; RAM_BANK_SIZE]>,
  rombank_selected: u8,
  rombanks: Vec<[u8; ROM_BANK_SIZE]>,
  memorymodel: u8,
}

impl MBC1 {
  pub fn new(header: CartridgeHeader, byts: &[u8]) -> Self {
    let num_rambanks = header.ram_size.0;
    let num_rombanks = header.rom_size.0;

    let mut rombanks = vec![[0_u8; ROM_BANK_SIZE]; num_rombanks];
    for (bank_num, bank)  in rombanks.iter_mut().enumerate() {
      for byte in 0..ROM_BANK_SIZE {
        bank[byte] = byts[(bank_num * ROM_BANK_SIZE) + byte];
      }
    }

    Self {
      header,
      memorymodel: 0,
      rambank_enabled: false,
      rambank_selected: 0,
      rambanks: vec![[0; RAM_BANK_SIZE]; num_rambanks],
      rombank_selected: 1,
      rombanks,
    }
  }
}

impl Cartridge for MBC1 {
  fn get_header(&self) -> &CartridgeHeader {
    &self.header
  }

  fn set(&mut self, index: u16, byt: u8) {
    if (0x0000..0x2000).contains(&index) {
      self.rambank_enabled = (byt & 0b00001111) == 0b1010
    }
  }
}

impl Index<u16> for MBC1 {
  type Output = u8;

  fn index(&self, index: u16) -> &Self::Output {
    if (0x0000..0x4000).contains(&index) {
      &self.rombanks[0][index as usize]
    } else if (0x4000..0x8000).contains(&index) {
      &self.rombanks[self.rombank_selected as usize][index as usize - 0x4000]
    } else if (0xA000..0xC000).contains(&index) {
      if self.rambank_enabled {
        &self.rambanks[self.rambank_selected as usize][index as usize - 0xA000]
      } else {
        &0xFF
      }
    } else {
      panic!("Read index is out of bounds");
    }
  }
}