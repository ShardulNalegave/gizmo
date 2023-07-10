
// ===== Imports =====
use crate::clock::Clock;
// ===================


pub struct Registers {
  a: u8,
  b: u8,
  c: u8,
  d: u8,
  e: u8,
  f: u8,
  h: u8,
  l: u8,
  last_instruction_clock: Clock,
}

pub enum RegisterPair {
  AF,
  BC,
  DE,
  HL,
}

impl Registers {
  pub fn new() -> Self {
    Self {
      a: 0,
      b: 0,
      c: 0,
      d: 0,
      e: 0,
      f: 0,
      h: 0,
      l: 0,
      last_instruction_clock: Clock::new(),
    }
  }
}