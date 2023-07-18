
pub mod cart_type;

// ===== Imports =====
use crate::cartridge::cart_type::CartridgeMetadata;
// ===================

pub struct Cartridge {
  title: String,
  meta: CartridgeMetadata,
  destination_code: DestinationCode,
  byts: Vec<u8>,
}

impl Cartridge {
  pub fn new(byts: Vec<u8>) -> Self {
    let meta = CartridgeMetadata::from(byts[0x0147]);
    let title = String::from_utf8(byts[0x0134..=0x0142].to_vec()).expect("Couldn't parse ROM Title");

    let destination_code;
    match byts[0x014A] {
      0 => destination_code = DestinationCode::Japanese,
      1 => destination_code = DestinationCode::NonJapanese,
      _ => panic!("Invalid Destination Code"),
    }

    Self {
      title, meta, destination_code, byts,
    }
  }

  pub fn len(&self) -> usize {
    self.byts.len()
  }

  pub fn get(&self, pos: usize) -> u8 {
    self.byts[pos]
  }
}

pub enum DestinationCode {
  Japanese = 0,
  NonJapanese = 1,
}