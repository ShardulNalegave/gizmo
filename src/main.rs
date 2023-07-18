
mod io;
mod display;
mod cpu;
mod clock;
mod memory;
mod registers;
mod instructions;
mod cartridge;

// ===== Imports =====
use std::{env, fs::File, io::Read};
use crate::cartridge::Cartridge;
use crate::instructions::Instructions;
use crate::registers::Register;
// ===================

fn main() {
  let args: Vec<String> = env::args().collect();

  // Load the ROM
  let rom_loc = args[1].as_str();
  let mut rom = File::open(rom_loc)
    .expect("Could not load GameBoy ROM");
  let mut rom_buffer = Vec::new();
  rom.read_to_end(&mut rom_buffer).expect("Could not read bytes from ROM");

  let cart = Cartridge::new(rom_buffer);
  let mut gb_cpu = cpu::CPU::new();

  while gb_cpu.registers.get_u16(Register::PC) < cart.len() as u16 {
    let byt = cart.get(gb_cpu.registers.get_u16(Register::PC) as usize);
    Instructions::execute(byt, &cart, &mut gb_cpu.registers);
  }
}
