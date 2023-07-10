
// ===== Imports =====
use super::Instruction;
// ===================

pub struct InstructionReader;
impl InstructionReader {
  pub fn instructions_from_bytes(byts: Vec<u8>) -> Vec<Instruction> {
    let instrs_vec = Vec::new();
    let mut curr_byt_ptr = 0;

    while curr_byt_ptr < byts.len() {
      let byt = byts[curr_byt_ptr];
      match byt {
        _ => {
          println!("Unknown Opcode: {:?}", byt);
          break;
        },
      }
    }

    instrs_vec
  }
}