
pub struct CartridgeMetadata {
  pub cart_type: CartridgeType,
  pub sram: bool,
  pub battery: bool,
  pub rtc: bool,
}

impl From<u8> for CartridgeMetadata {
  fn from(code: u8) -> Self {
    match code {
      0x00 => CartridgeMetadata {
        cart_type: CartridgeType::ROMOnly,
        sram: false,
        battery: false,
        rtc: false,
      }, // RAM-Only
      0x01 => CartridgeMetadata {
        cart_type: CartridgeType::MBC1,
        sram: false,
        battery: false,
        rtc: false,
      }, // MBC-1
      0x02 => CartridgeMetadata {
        cart_type: CartridgeType::MBC1,
        sram: true,
        battery: false,
        rtc: false,
      }, // MBC-1 + RAM
      0x03 => CartridgeMetadata {
        cart_type: CartridgeType::MBC1,
        sram: true,
        battery: true,
        rtc: false,
      }, // MBC-1 + RAM + BATT
      0x05 => CartridgeMetadata {
        cart_type: CartridgeType::MBC2,
        sram: false,
        battery: false,
        rtc: false,
      }, // MBC-2
      0x06 => CartridgeMetadata {
        cart_type: CartridgeType::MBC2,
        sram: false,
        battery: true,
        rtc: false,
      }, // MBC-2 + BATT
      0x08 => CartridgeMetadata {
        cart_type: CartridgeType::ROMOnly,
        sram: true,
        battery: false,
        rtc: false,
      }, // ROM + RAM
      0x09 => CartridgeMetadata {
        cart_type: CartridgeType::ROMOnly,
        sram: true,
        battery: true,
        rtc: false,
      }, // ROM + RAM + BATT
      0x0F => CartridgeMetadata {
        cart_type: CartridgeType::MBC3,
        sram: false,
        battery: true,
        rtc: true,
      }, // MBC-3 + BATT + TIMER
      0x10 => CartridgeMetadata {
        cart_type: CartridgeType::MBC3,
        sram: true,
        battery: true,
        rtc: true,
      }, // MBC-3 + RAM + BATT + TIMER
      0x11 => CartridgeMetadata {
        cart_type: CartridgeType::MBC3,
        sram: false,
        battery: false,
        rtc: false,
      }, // MBC-3
      0x12 => CartridgeMetadata {
        cart_type: CartridgeType::MBC3,
        sram: true,
        battery: false,
        rtc: false,
      }, // MBC-3 + RAM
      0x13 => CartridgeMetadata {
        cart_type: CartridgeType::MBC3,
        sram: true,
        battery: true,
        rtc: false,
      }, // MBC-3 + RAM + BATT
      0x19 => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: false,
        battery: false,
        rtc: false,
      }, // MBC-5
      0x1A => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: true,
        battery: false,
        rtc: false,
      }, // MBC-5 + RAM
      0x1B => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: true,
        battery: true,
        rtc: false,
      }, // MBC-5 + RAM + BATT
      0x1C => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: false,
        battery: false,
        rtc: false,
      }, // MBC-5 + RUMBLE
      0x1D => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: true,
        battery: false,
        rtc: false,
      }, // MBC-5 + RUMBLE + RAM
      0x1E => CartridgeMetadata {
        cart_type: CartridgeType::MBC5,
        sram: true,
        battery: true,
        rtc: false,
      }, // MBC-5 + RUMBLE + RAM + BATT
      _ => panic!("No valid Cartridge-Metadata for this code"),
    }
  }
}

pub enum CartridgeType {
  ROMOnly,
  MBC1,
  MBC2,
  MBC3,
  MBC5,
}
