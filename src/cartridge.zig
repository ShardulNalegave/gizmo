pub const Cartridge = struct {
    ptr: *anyopaque,
    getFn: *const fn (ptr: *anyopaque, index: u16) anyerror!u8,

    pub fn get(self: *Cartridge, index: u16) anyerror!u8 {
        return self.getFn(self.ptr, index);
    }
};
