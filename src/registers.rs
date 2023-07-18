
pub mod flag;

// ===== Imports =====
use crate::clock::Clock;
// ===================

#[derive(Debug)]
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

#[derive(Copy, Clone, Debug)]
pub enum Register {
  // Accumulator
  A,
  B,
  C,
  D,
  E,
  // Flags
  F,
  H,
  L,
  AF,
  BC,
  DE,
  HL,
  SP,
  PC,
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

  pub fn get_u8(&self, reg: Register) -> u8 {
    match reg {
      Register::A => self.a,
      Register::B => self.b,
      Register::C => self.c,
      Register::D => self.d,
      Register::E => self.e,
      Register::F => self.f,
      Register::H => self.h,
      Register::L => self.l,
      _ => panic!("Given register is not 8-bit"),
    }
  }

  pub fn get_u16(&self, reg: Register) -> u16 {
    match reg {
      Register::AF => {
        let high = self.a as u16;
        let low = self.f as u16;

        (high << 8) | low
      },
      Register::BC => {
        let high = self.b as u16;
        let low = self.c as u16;

        (high << 8) | low
      },
      Register::DE => {
        let high = self.d as u16;
        let low = self.e as u16;

        (high << 8) | low
      },
      Register::HL => {
        let high = self.h as u16;
        let low = self.l as u16;

        (high << 8) | low
      },
      Register::SP => self.sp,
      Register::PC => self.pc,
      _ => panic!("Given register is not 16-bit"),
    }
  }

  pub fn set_u8(&mut self, reg: Register, val: u8) {
    match reg {
      Register::A => self.a = val,
      Register::B => self.b = val,
      Register::C => self.c = val,
      Register::D => self.d = val,
      Register::E => self.e = val,
      Register::F => self.f = val,
      Register::H => self.h = val,
      Register::L => self.l = val,
      _ => panic!("Given register is not 8-bit"),
    }
  }

  pub fn set_u16(&mut self, reg: Register, val: u16) {
    match reg {
      Register::AF => {
        let high = ((val & 0xFF00) >> 8) as u8;
        let low = (val & 0xFF) as u8;
        self.a = high;
        self.f = low;
      },
      Register::BC => {
        let high = ((val & 0xFF00) >> 8) as u8;
        let low = (val & 0xFF) as u8;
        self.b = high;
        self.c = low;
      },
      Register::DE => {
        let high = ((val & 0xFF00) >> 8) as u8;
        let low = (val & 0xFF) as u8;
        self.d = high;
        self.e = low;
      },
      Register::HL => {
        let high = ((val & 0xFF00) >> 8) as u8;
        let low = (val & 0xFF) as u8;
        self.h = high;
        self.l = low;
      },
      Register::SP => self.sp = val,
      Register::PC => self.pc = val,
      _ => panic!("Given register is not 16-bit"),
    }
  }
}
