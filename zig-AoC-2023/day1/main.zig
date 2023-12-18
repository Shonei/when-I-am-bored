const std = @import("std");
const print = std.debug.print;

const number = struct { s: []const u8, val: u8 };

pub fn main() !void {
    var start = std.time.milliTimestamp();

    var zero = number{
        .s = "zero",
        .val = 0,
    };
    var one = number{
        .s = "one",
        .val = 1,
    };
    var two = number{
        .s = "two",
        .val = 2,
    };
    var three = number{
        .s = "three",
        .val = 3,
    };
    var four = number{
        .s = "four",
        .val = 4,
    };
    var five = number{
        .s = "five",
        .val = 5,
    };
    var six = number{
        .s = "six",
        .val = 6,
    };
    var seven = number{
        .s = "seven",
        .val = 7,
    };
    var eight = number{
        .s = "eight",
        .val = 8,
    };
    var nine = number{
        .s = "nine",
        .val = 9,
    };

    const digits = [_]number{ zero, one, two, three, four, five, six, seven, eight, nine };

    var lines = std.mem.split(u8, @embedFile("input.txt"), "\n");
    var total: i32 = 0;

    while (lines.next()) |line| {
        var first: ?u8 = null;
        var last: ?u8 = null;

        for (0.., line) |i, char| {

            // found a number
            if (char >= 48 and char <= 57) {
                const numVal = char - 48;
                if (first == null) {
                    first = numVal;
                } else {
                    last = numVal;
                }

                continue;
            }

            for (digits) |digit| {
                if (line.len - i >= digit.s.len and std.mem.eql(u8, digit.s, line[i .. i + digit.s.len])) {
                    // print("Found {s} {s}\n", .{ digit.s, line });
                    if (first == null) {
                        first = digit.val;
                    } else {
                        last = digit.val;
                    }
                }
            }
        }

        // if there was never a second char
        if (last == null) {
            last = first;
        }

        print("Digint {any}{any}\n", .{ first, last });
        total += (first.? * 10) + last.?;
    }

    print("Total score = {any}\n", .{total});
    print("Time - {any}ms", .{std.time.milliTimestamp() - start});
}
