const registers = @import("./cpu/registers.zig");
const memory = @import("./memory.zig");
const cartridge = @import("./cartridge.zig");

pub const CPU = struct {
    registers: registers.Registers,
    memory: memory.Memory,

    pub fn new(cart: cartridge.Cartridge) CPU {
        return CPU{
            .registers = registers.Registers.new(),
            .memory = memory.Memory.new(cart),
        };
    }
};
