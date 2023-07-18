
pub enum CartridgeType {
  ROM,
  MBC1,
  MBC2,
  MBC3,
  MBC5,
}

pub fn get_cartridge_type(code: u8) -> (CartridgeType, bool, bool, bool) { // Returns (type, sram, battery, rtc)
  match code {
    0x00 => (CartridgeType::ROM, false, false, false), // ROM-Only
    0x08 => (CartridgeType::ROM, true, false, false), // ROM + RAM
    0x09 => (CartridgeType::ROM, true, true, false), // ROM + RAM + BATT
    0x01 => (CartridgeType::MBC1, false, false, false), // MBC-1
    0x02 => (CartridgeType::MBC1, true, false, false), // MBC-1 + RAM
    0x03 => (CartridgeType::MBC1, true, true, false), // MBC-1 + RAM + BATT
    0x05 => (CartridgeType::MBC2, false, false, false), // MBC-2
    0x06 => (CartridgeType::MBC2, false, true, false), // MBC-2 + BATT
    0x0F => (CartridgeType::MBC3, false, true, true), // MBC-3 + BATT + TIMER
    0x10 => (CartridgeType::MBC3, true, true, true), // MBC-3 + RAM + BATT + TIMER
    0x11 => (CartridgeType::MBC3, false, false, false), // MBC-3
    0x12 => (CartridgeType::MBC3, true, false, false), // MBC-3 + RAM
    0x13 => (CartridgeType::MBC3, true, true, false), // MBC-3 + RAM + BATT
    0x19 => (CartridgeType::MBC5, false, false, false), // MBC-5
    0x1A => (CartridgeType::MBC5, true, false, false), // MBC-5 + RAM
    0x1B => (CartridgeType::MBC5, true, true, false), // MBC-5 + RAM + BATT
    0x1C => (CartridgeType::MBC5, false, false, false), // MBC-5 + RUMBLE
    0x1D => (CartridgeType::MBC5, true, false, false), // MBC-5 + RUMBLE + RAM
    0x1E => (CartridgeType::MBC5, true, true, false), // MBC-5 + RUMBLE + RAM + BATT
    _ => panic!("No valid Cartridge-Metadata for this code"),
  }
}