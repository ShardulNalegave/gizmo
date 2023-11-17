
pub const IO_PORT_LENGTH: usize = 0x4C;
pub const UNUSABLE_IO_RAM0_LENGTH: usize = 0x60;
pub const UNUSABLE_IO_RAM1_LENGTH: usize = 0x34;

pub struct IO {
  pub io_ports: [u8; IO_PORT_LENGTH],
  pub unusable_io_ram0: [u8; UNUSABLE_IO_RAM0_LENGTH],
  pub unusable_io_ram1: [u8; UNUSABLE_IO_RAM1_LENGTH]
}

impl IO {
  pub fn new() -> Self {
    Self {
      io_ports: [0; IO_PORT_LENGTH],
      unusable_io_ram0: [0; UNUSABLE_IO_RAM0_LENGTH],
      unusable_io_ram1: [0; UNUSABLE_IO_RAM1_LENGTH],
    }
  }
}