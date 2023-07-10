
mod cpu;
mod clock;
mod registers;
mod instructions;

// ===== Imports =====
use std::{fs::File, io::Read};
use instructions::reader::InstructionReader;
// ===================

fn main() {
  // Load a test-ROM
  let mut rom = File::open("testROMs/Pokemon_Red.gb")
    .expect("Could not load GameBoy ROM");
  let mut rom_buffer = Vec::new();
  rom.read_to_end(&mut rom_buffer).expect("Could not read bytes from ROM");
  let rom_instructions = InstructionReader::instructions_from_bytes(rom_buffer);

  let game_boy = cpu::CPU::new();

  for instr in rom_instructions {
    //
  }
}
