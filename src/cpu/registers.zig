pub const Flags = enum(u8) {
    CARRY = 0b0001_0000,
    HALF_CARRY = 0b0010_0000,
    SUBTRACTION = 0b0100_0000,
    ZERO = 0b1000_0000,
};

pub const Registers = struct {
    a: u8,
    b: u8,
    c: u8,
    d: u8,
    e: u8,
    f: u8,
    h: u8,
    l: u8,
    sp: u16,
    pc: u16,

    pub fn new() Registers {
        return Registers{
            // TODO: Put init values
        };
    }

    pub fn af(self: *Registers) u16 {
        return (self.a << 8) | self.f;
    }

    pub fn bc(self: *Registers) u16 {
        return (self.b << 8) | self.c;
    }

    pub fn de(self: *Registers) u16 {
        return (self.d << 8) | self.e;
    }

    pub fn hl(self: *Registers) u16 {
        return (self.h << 8) | self.l;
    }

    pub fn set_af(self: *Registers, value: u16) void {
        self.a = value >> 8;
        self.f = value & 0x0F;
    }

    pub fn set_bc(self: *Registers, value: u16) void {
        self.b = value >> 8;
        self.c = value & 0x0F;
    }

    pub fn set_de(self: *Registers, value: u16) void {
        self.d = value >> 8;
        self.e = value & 0x0F;
    }

    pub fn set_flag(self: *Registers, value: u16) void {
        self.f = value;
    }

    pub fn is_flag_set(self: *Registers, flag: u8) bool {
        return (self.f & flag) != 0;
    }
};
