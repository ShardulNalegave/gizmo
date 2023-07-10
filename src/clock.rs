
#[derive(Debug)]
pub struct Clock {
  m: usize,
  t: usize,
}

impl Clock {
  pub fn new() -> Self {
    Self {
      m: 0,
      t: 0,
    }
  }
}