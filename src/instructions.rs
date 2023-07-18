#![allow(non_snake_case)]

// ===== Imports =====
use crate::{
  cartridge::Cartridge,
  registers::{Register, Registers},
};
// ===================

pub struct Instructions;
impl Instructions {
  pub fn get_opcode_len(opcode: u8) -> u8 {
    match opcode {
      0x00 => 1,
      _ => 0,
    }
  }

  pub fn execute(opcode: u8, cart: &Cartridge, reg: &mut Registers) -> usize {
    let opcode_len = Instructions::get_opcode_len(opcode);
    let pc = reg.get_u16(Register::PC) as usize;
    let mut v = 0;

    if opcode_len == 2 {
      v = cart.get_byte(pc + 1);
    } else if opcode_len == 3 {
      let low = cart.get_byte(pc + 1);
      let high = cart.get_byte(pc + 2);
      v = (high << 8) + low;
    }

    reg.set_u16(Register::PC, (pc + opcode_len as usize) as u16);

    match opcode {
      0x00 => NOP_00(reg),
      _ => 0,
    }
  }
}

// 0x00 -> NOP
fn NOP_00(reg: &mut Registers) -> usize {
  4
}