
pub struct Flag {
  pub zero: bool,
  pub negative: bool,
  pub half_carry: bool,
  pub carry: bool,
}

impl Into<u8> for Flag {
  fn into(self) -> u8 {
    let mut val = 0b0000_0000;

    if self.zero {
      val = val | 0b1000_0000;
    }

    if self.negative {
      val = val | 0b0100_0000;
    }

    if self.half_carry {
      val = val | 0b0010_0000;
    }

    if self.carry {
      val = val | 0b0001_0000;
    }

    val
  }
}

impl From<u8> for Flag {
  fn from(value: u8) -> Self {
    let mut zero = false;
    let mut negative = false;
    let mut half_carry = false;
    let mut carry = false;

    if (value & 0b1000_0000) != 0 {
      zero = true;
    }

    if (value & 0b0100_0000) != 0 {
      negative = true;
    }

    if (value & 0b0010_0000) != 0 {
      half_carry = true;
    }

    if (value & 0b0001_0000) != 0 {
      carry = true;
    }

    Flag {
      zero, negative, half_carry, carry,
    }
  }
}