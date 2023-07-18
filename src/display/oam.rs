
// ===== Imports =====
use std::ops::Index;
// ===================

const OAM_LENGTH: usize = 0xA0;

pub struct ObjectAttribMemory {
  byts: [u8; OAM_LENGTH],
}

impl ObjectAttribMemory {
  pub fn new() -> Self {
    Self {
      byts: [0; OAM_LENGTH],
    }
  }
}

impl Index<usize> for ObjectAttribMemory {
  type Output = u8;

  fn index(&self, index: usize) -> &Self::Output {
    &self.byts[index]
  }
}