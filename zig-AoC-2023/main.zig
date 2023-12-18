const std = @import("std");
const print = std.debug.print;

const arr: [1]f16 = .{1.1};

pub fn main() !void {
    var i: i32 = 0;
    print("{any}", .{arr[@as(usize, @intCast(i))]});
}
