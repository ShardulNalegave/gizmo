const cartridge = @import("../cartridge.zig");
const header = @import("./header.zig");

pub const ROMOnly = struct {
    header: header.CartridgeHeader,

    pub fn asCartridge(self: *ROMOnly) cartridge.Cartridge {
        return cartridge.Cartridge{
            .ptr = self,
            .getFn = get,
        };
    }

    pub fn get(self: *ROMOnly, index: u16) u8 {
        return 0;
    }
};
