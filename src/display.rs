
pub mod vram;
pub mod oam;

// ===== Imports =====
use crate::display::oam::ObjectAttribMemory;
use crate::display::vram::VideoRAM;
// ===================

pub struct Display {
  pub vram: VideoRAM, // 8kB VRAM (0x8000 - 0xA000)
  pub oam: ObjectAttribMemory, // 0xA0 Object/Sprite Attribute Memory (0xFE00 - 0xFEA0)
}

impl Display {
  pub fn new() -> Self {
    Self {
      vram: VideoRAM::new(),
      oam: ObjectAttribMemory::new(),
    }
  }
}