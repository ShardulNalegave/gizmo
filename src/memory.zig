const vram = @import("./vram.zig");
const oam = @import("./graphics/oam.zig");
const io = @import("./io.zig");

pub const WRAM_OFFSET = 0xC000;
pub const WRAM_LEN = 0xE000 - 0xC000;

pub const Memory = struct {
    wram: [WRAM_LEN]u8,
    ie: u8,

    pub fn new() Memory {
        return Memory{};
    }

    pub fn get(self: *Memory, index: u16) u8 {
        switch (index) {
            0x0000...0x4000 => {
                //
            },

            0x4000...0x8000 => {
                //
            },

            vram.VRAM_OFFSET...0xA000 => {
                //
            },

            0xA000...0xC000 => {
                //
            },

            WRAM_OFFSET...0xE000 => {
                return self.wram[index - WRAM_OFFSET];
            },

            0xE000...0xFE00 => {
                // 0xE000-0xFDFF is basically mapped to 0xC000-0xDDFF
                return self.wram[index - 0xE000];
            },

            oam.OAM_OFFSET...0xFEA0 => {
                // OAM
            },

            0xFEA0...0xFF00 => {
                // not usable
                return 0x00;
            },

            io.IO_REGISTERS_OFFSET...0xFF80 => {
                //
            },

            0xFF80...0xFFFF => {
                // HRAM
            },

            0xFFFF => {
                return self.ie;
            },

            else => unreachable,
        }
    }
};
