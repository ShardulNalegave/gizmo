
// ===== Imports =====
use std::ops::Index;
// ===================

const VRAM_LENGTH: usize = 8 * 1024; // 8kB VRAM

pub struct VideoRAM {
  byts: [u8; VRAM_LENGTH],
}

impl VideoRAM {
  pub fn new() -> Self {
    Self {
      byts: [0; VRAM_LENGTH],
    }
  }
}

impl Index<usize> for VideoRAM {
  type Output = u8;

  fn index(&self, index: usize) -> &Self::Output {
    &self.byts[index]
  }
}