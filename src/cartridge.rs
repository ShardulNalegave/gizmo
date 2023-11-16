
pub mod cart_type;
pub mod header;

pub mod rom;

// ===== Imports =====
use std::ops::{Index, IndexMut};
use anyhow::Result;

use crate::cartridge::{
  cart_type::CartridgeType,
  header::CartridgeHeader,
  rom::ROM,
};
// ===================

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

pub trait Cartridge: Index<u16, Output=u8> + IndexMut<u16, Output=u8> {
  fn get_header(&self) -> &CartridgeHeader;
}

pub fn get_cartridge(byts: &[u8]) -> Result<Box<dyn Cartridge>> {
  let header = CartridgeHeader::from(byts)?;

  Ok(Box::new(match header.cart_type {
    CartridgeType::ROM => ROM::new(header, byts),
    _ => unimplemented!(),
  }))
}