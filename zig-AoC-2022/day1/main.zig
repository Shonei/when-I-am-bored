const std = @import("std");

pub fn main() !u8 {
    var gp = std.heap.GeneralPurposeAllocator(.{ .safety = true }){};
    defer _ = gp.deinit();
    const allocator = gp.allocator();

    var file = std.fs.Dir.openFile("C:/Users/ASUS/OneDrive/Documents/Projects/when-I-am-bored/zig-AoC-2022/day1/cal.txt", .{ .mode = std.fs.File.OpenMode.read_only }) catch |err| {
        std.log.err("{}", .{err});
        return @as(u8, 1);
    };
    defer file.close();

    const buffer_size = 2000;
    const file_buffer = file.readToEndAlloc(allocator, buffer_size) catch |err| {
        std.log.err("{}", .{err});
        return @as(u8, 1);
    };
    defer allocator.free(file_buffer);

    var iter = std.mem.split(u8, file_buffer, "\n");

    var count: usize = 0;
    var max: i32 = 0;
    var total: i32 = 0;
    while (iter.next()) |line| : (count += 1) {
        if (line.len == 1) {
            std.log.info("Total: {}", .{total});

            if (max < total) {
                max = total;
            }
            total = 0;
        } else {
            var s = std.mem.sliceTo(line, 13);
            const item = std.fmt.parseInt(i32, s, 10) catch |err| {
                std.log.err("{} {d}", .{ err, line });
                return @as(u8, 1);
            };
            total = total + item;
        }
    }

    if (max < total) {
        max = total;
    }

    std.log.info("Total: {}", .{total});
    std.debug.print("Max {d}", .{max});

    return @as(u8, 0);
}
