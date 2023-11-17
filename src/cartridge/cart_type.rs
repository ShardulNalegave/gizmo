
// ===== Imports =====
use anyhow::{Result, anyhow};
use crate::cartridge::CartridgeError;
// ===================

#[derive(Clone, Copy, Debug)]
pub enum CartridgeType {
  ROM,
  MBC1,
  MBC2,
  MBC3,
  MBC5,
}

pub fn get_cartridge_type(code: u8) -> Result<(CartridgeType, bool, bool, bool)> { // Returns (type, sram, battery, rtc)
  match code {
    0x00 => Ok((CartridgeType::ROM, false, false, false)),
    0x01 => Ok((CartridgeType::MBC1, false, false, false)),
    0x02 => Ok((CartridgeType::MBC1, true, false, false)),
    0x03 => Ok((CartridgeType::MBC1, true, true, false)),
    0x05 => Ok((CartridgeType::MBC2, false, false, false)),
    0x06 => Ok((CartridgeType::MBC2, false, true, false)),
    0x08 => Ok((CartridgeType::ROM, true, false, false)),
    0x09 => Ok((CartridgeType::ROM, true, true, false)),
    0x0F => Ok((CartridgeType::MBC3, false, true, true)),
    0x10 => Ok((CartridgeType::MBC3, true, true, true)),
    0x11 => Ok((CartridgeType::MBC3, false, false, false)),
    0x12 => Ok((CartridgeType::MBC3, true, false, false)),
    0x13 => Ok((CartridgeType::MBC3, true, true, false)),
    0x19 => Ok((CartridgeType::MBC5, false, false, false)),
    0x1A => Ok((CartridgeType::MBC5, true, false, false)),
    0x1B => Ok((CartridgeType::MBC5, true, true, false)),
    _ => Err(anyhow!(CartridgeError::CouldntGetCartridgeType { code })),
  }
}