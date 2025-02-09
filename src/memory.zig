const constants = @import("./memory/constants.zig");

pub const Memory = struct {
    pub fn get(self: *Memory, index: u16) u8 {
        if (index <= 0x4000) {
            //
        } else if (index <= 0x8000) {
            //
        }
    }
};
