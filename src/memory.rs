
// ===== Imports =====
use crate::cartridge::Cartridge;
use crate::display::Display;
use crate::io::IO;
// ===================

const INTERNAL_RAM0: usize = 8 * 1024; // 8kB of Internal RAM
const INTERNAL_RAM1: usize = 0x7F; // More Internal RAM

pub struct Memory {
  io: IO,
  display: Display,
  cartridge: Box<dyn Cartridge>, // 32kB Cartridge (0x0000 - 0x8000)
  internal_ram0: [u8; INTERNAL_RAM0], // 8kB Internal RAM
  internal_ram1: [u8; INTERNAL_RAM1], // More Internal RAM
  interrupt_enable_register: u8,
}

impl Memory {
  pub fn get(&self, pos: u16) -> u8 {
    if (0x0000..0x8000).contains(&pos) { // 32kB Cartridge
      self.cartridge.get(pos)
    } else if (0x8000..0xA000).contains(&pos) { // 8kB VRAM
      self.display.vram[pos - 0x8000]
    } else if (0xA000..0xC000).contains(&pos) { // 8kB Switchable RAM Bank
      self.cartridge.get(pos)
    } else if (0xC000..0xE000).contains(&pos) { // 8kB Internal RAM
      self.internal_ram0[pos - 0xC000]
    } else if (0xE000..0xFE00).contains(&pos) { // Echo of 8kB Internal RAM
      self.internal_ram0[pos - 0xE000]
    } else if (0xFE00..0xFEA0).contains(&pos) { // 0xA0 Object/Sprite Attribute Memory
      self.display.oam[pos - 0xFE00]
    } else if (0xFEA0..0xFF00).contains(&pos) { // Empty but unusable for I/O
      self.io.unusable_io_ram0[pos - 0xFEA0]
    } else if (0xFF00..0xFF4C).contains(&pos) { // I/O Ports
      self.io.io_ports[pos - 0xFF00]
    } else if (0xFF4C..0xFF80).contains(&pos) { // Empty but unusable for I/O
      self.io.unusable_io_ram1[pos - 0xFF4C]
    } else if (0xFF80..0xFFFF).contains(&pos) { // More Internal RAM
      self.internal_ram1[pos - 0xFF80]
    } else if pos == 0xFFFF { // Interrupt Enable Register
      self.interrupt_enable_register
    } else {
      panic!("Memory position provided is out-of-bounds");
    }
  }
}