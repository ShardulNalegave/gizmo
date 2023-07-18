
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
use crate::cartridge::{Cartridge, new_cartridge};
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

  let cart = new_cartridge(rom_buffer);
  let mut gb_cpu = cpu::CPU::new();
}
