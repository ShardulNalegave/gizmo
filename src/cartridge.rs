
pub mod cart_type;
pub mod header;

pub mod rom;
pub mod mbc1;

// ===== Imports =====
use std::ops::Index;
use anyhow::Result;

use crate::cartridge::{
  cart_type::CartridgeType,
  header::CartridgeHeader,
  rom::ROM,
  mbc1::MBC1,
};
// ===================

pub const ROM_BANK_SIZE: usize = 16 * 1024;
pub const RAM_BANK_SIZE: usize = 8 * 1024;

#[derive(Clone, Copy, Debug)]
pub enum CartridgeError {
  CouldntGetCartridgeType { code: u8 },
}

impl std::fmt::Display for CartridgeError {
  fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
    match self {
      CartridgeError::CouldntGetCartridgeType { code } => write!(f, "Couldn't infer Cartridge-Type (code: {})", code),
    }
  }
}

// ==================================================================================================================================

pub trait Cartridge: Index<u16, Output=u8> {
  fn get_header(&self) -> &CartridgeHeader;
  fn set(&mut self, index: u16, byt: u8);
}

pub fn get_cartridge(byts: &[u8]) -> Result<Box<dyn Cartridge>> {
  let header = CartridgeHeader::from(byts)?;

  Ok(match header.cart_type {
    CartridgeType::ROM => Box::new(ROM::new(header, byts)),
    CartridgeType::MBC1 => Box::new(MBC1::new(header, byts)),
    _ => unimplemented!(),
  })
}