
// ===== Imports =====
use derive_getters::Getters;
use crate::clock::Clock;
// ===================

#[derive(Debug, Getters)]
pub struct Registers {
  a: u8,
  b: u8,
  c: u8,
  d: u8,
  e: u8,
  f: u8,
  h: u8,
  l: u8,
  sp: u16,
  pc: u16,
  last_instruction_clock: Clock,
}

pub enum Register {
  A(u8),
  B(u8),
  C(u8),
  D(u8),
  E(u8),
  F(u8),
  H(u8),
  L(u8),
  AF(u16),
  BC(u16),
  DE(u16),
  HL(u16),
  SP(u16),
  PC(u16),
}

pub enum Flag {
  Zero = 0b10000000,
  Negative = 0b01000000,
  HalfCarry = 0b00100000,
  Carry = 0b00010000,
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
      sp: 0xFFFE,
      pc: 0x100,
      last_instruction_clock: Clock::new(),
    }
  }

  pub fn af(&self) -> u16 {
    let high = self.a as u16;
    let low = self.f as u16;
    
    (high << 8) | low
  }

  pub fn bc(&self) -> u16 {
    let high = self.b as u16;
    let low = self.c as u16;

    (high << 8) | low
  }

  pub fn de(&self) -> u16 {
    let high = self.d as u16;
    let low = self.e as u16;

    (high << 8) | low
  }

  pub fn hl(&self) -> u16 {
    let high = self.h as u16;
    let low = self.l as u16;

    (high << 8) | low
  }

  pub fn modify(&mut self, reg: Register) {
    match reg {
      Register::A(val) => self.a = val,
      Register::B(val) => self.b = val,
      Register::C(val) => self.c = val,
      Register::D(val) => self.d = val,
      Register::E(val) => self.e = val,
      Register::F(val) => self.f = val,
      Register::H(val) => self.h = val,
      Register::L(val) => self.l = val,
      Register::AF(val) => {
        let high = (val >> 8) as u8;
        let low = val as u8;
        self.a = high;
        self.f = low;
      },
      Register::BC(val) => {
        let high = (val >> 8) as u8;
        let low = val as u8;
        self.b = high;
        self.c = low;
      },
      Register::DE(val) => {
        let high = (val >> 8) as u8;
        let low = val as u8;
        self.d = high;
        self.e = low;
      },
      Register::HL(val) => {
        let high = (val >> 8) as u8;
        let low = val as u8;
        self.h = high;
        self.l = low;
      },
      Register::SP(val) => self.sp = val,
      Register::PC(val) => self.pc = val,
    }
  }
}