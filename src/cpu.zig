const registers = @import("./cpu/registers.zig");
const memory = @import("./memory.zig");

pub const CPU = struct {
    registers: registers.Registers,
    memory: memory.Memory,

    pub fn new() CPU {
        return CPU{
            .registers = registers.Registers.new(),
            .memory = memory.Memory.new(),
        };
    }
};
