
// ===== Imports =====
use crate::{registers::Registers, clock::Clock, instructions::Instruction};
// ===================


pub struct CPU {
  registers: Registers,
  clock: Clock,
}

impl CPU {
  pub fn new() -> Self {
    Self {
      registers: Registers::new(),
      clock: Clock::new(),
    }
  }

  pub fn process_instruction(instr: Instruction) {
    unimplemented!()
  }
}