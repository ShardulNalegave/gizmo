const constants = @import("./memory/constants.zig");

pub const MemoryError = error{
    InvalidMemoryAddress,
};

pub const Memory = struct {
    wram: [constants.ECHO_RAM - constants.WRAM]u8,

    pub fn new() Memory {
        return Memory{};
    }

    pub fn get(self: *Memory, index: u16) MemoryError!u8 {
        switch (index) {
            constants.ROM_BANK_00...constants.ROM_BANK_SELECTABLE => {
                //
            },

            constants.ROM_BANK_SELECTABLE...constants.VRAM => {
                //
            },

            constants.VRAM...constants.EXTERNAL_RAM => {
                //
            },

            constants.EXTERNAL_RAM...constants.WRAM => {
                //
            },

            constants.WRAM...constants.ECHO_RAM => {
                return self.wram[index - constants.WRAM];
            },

            constants.ECHO_RAM...constants.OAM => {
                // 0xE000-0xFDFF is basically mapped to 0xC000-0xDDFF
                return self.wram[index - constants.ECHO_RAM];
            },

            constants.OAM...0xFEA0 => {
                // not usable
                return 0x00;
            },

            0xFEA0...constants.IO_REGISTERS => {
                //
            },

            constants.IO_REGISTERS...constants.HRAM => {
                //
            },

            constants.HRAM...constants.INTERRUPT_ENABLE_REGISTER => {
                //
            },

            constants.INTERRUPT_ENABLE_REGISTER => {
                //
            },

            else => return MemoryError.InvalidMemoryAddress,
        }
    }
};
