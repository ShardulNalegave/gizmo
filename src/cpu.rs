
// ===== Imports =====
use crate::{registers::Registers, clock::Clock};
// ===================

pub struct CPU {
  pub registers: Registers,
  pub clock: Clock,
}

impl CPU {
  pub fn new() -> Self {
    Self {
      registers: Registers::new(),
      clock: Clock::new(),
    }
  }
}