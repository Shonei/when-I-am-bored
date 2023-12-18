const std = @import("std");
const print = std.debug.print;

// rock -    A  X  - 1
// paper -   B  Y  - 2
// sissors - C  Z  - 3
pub fn main() !void {
    const lines = std.mem.bytesAsSlice([5]u8, @embedFile("input.txt"));
    var score: i32 = 0;
    for (lines) |line| {
        var me: i32 = @intCast(line[2] - 87);
        var oponent: i32 = @intCast(line[0] - 64);
        var roundScore: i32 = (((me - oponent) + 1) * 3) + me;
        score += roundScore;

        print("{any} {any} {any}\n", .{ me, oponent, roundScore });
    }

    print("Total score for me - {d}", .{score});
}
