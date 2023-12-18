const std = @import("std");
const print = std.debug.print;

const lineType = [142]u8;
const lineVisited = [142]bool;

const grid = struct {
    lines: []const lineType,
    visited: []lineVisited,
    const Self = @This();

    fn getNumber(self: Self, lineIndex: usize, i: usize) i32 {
        var startIndex: usize = 0;
        var endIndex: usize = 0;
        var line = self.lines[lineIndex];

        if (self.visited[lineIndex][i]) {
            // number olready visited
            return 0;
        }

        var s = i;
        while (s >= 0) {
            if (!isNumber(line[s])) {
                startIndex = s + 1;
                break;
            }

            self.visited[lineIndex][s] = true;

            if (s == 0) {
                break;
            }
            s = s - 1;
        }

        for (i..line.len) |e| {
            if (!isNumber(line[e])) {
                endIndex = e;
                break;
            }

            self.visited[lineIndex][e] = true;
        }

        // print("found number {s}\n", .{line[startIndex..endIndex]});
        return std.fmt.parseInt(i32, line[startIndex..endIndex], 10) catch {
            print("failed to parse - {any}\n", .{line[startIndex..endIndex]});
            return 0;
        };
    }

    fn init(allocator: std.mem.Allocator) !Self {
        const lines = std.mem.bytesAsSlice(lineType, @embedFile("input.txt"));
        const visited = try allocator.alloc(lineVisited, lines.len);

        return grid{ .lines = lines, .visited = visited };
    }

    fn free(self: Self, allocator: std.mem.Allocator) void {
        allocator.free(self.visited);
        return;
    }
};

fn isSymbol(char: u8) bool {
    return (char >= 33 and char <= 47 and char != 46) or (char >= 58 and char <= 64);
}

fn isNumber(char: u8) bool {
    return char >= 48 and char <= 57;
}

pub fn main() !void {
    var start = std.time.milliTimestamp();

    var gp = std.heap.GeneralPurposeAllocator(.{ .safety = true }){};
    defer _ = gp.deinit();
    const allocator = gp.allocator();

    var g = grid.init(allocator) catch |err| {
        print("failed to init array {any}\n", .{err});
        return;
    };
    defer g.free(allocator);

    var gs: i64 = 1;
    var adjasentNumbers: i32 = 0;

    var sum: i32 = 0;
    var gearSum: i128 = 0;
    for (0.., g.lines) |y, line| {
        for (0.., line) |x, char| {
            if (!isSymbol(char)) {
                continue; // not a symbol continue
            }

            // reset counters
            gs = 1;
            adjasentNumbers = 0;

            var startIndex = if (x == 0) 0 else x - 1;
            var endIndex = if (x == line.len - 1) x + 1 else x + 2;

            if (y > 0) {
                // check line above
                for (startIndex..endIndex) |i| {
                    if (isNumber(g.lines[y - 1][i])) {
                        var n = g.getNumber(y - 1, i);
                        sum += n;
                        if (char == 42 and n != 0) {
                            // print("n - {d} - {d}\n", .{ n, adjasentNumbers });
                            adjasentNumbers += 1;
                            gs = gs * n;
                        }
                    }
                }
            }

            if (y < g.lines.len - 1) {
                // check line bellow
                for (startIndex..endIndex) |i| {
                    if (isNumber(g.lines[y + 1][i])) {
                        var n = g.getNumber(y + 1, i);
                        sum += n;
                        if (char == 42 and n != 0) {
                            // print("n - {d} - {d}\n", .{ n, adjasentNumbers });
                            adjasentNumbers += 1;
                            gs = gs * n;
                        }
                    }
                }
            }

            if (x != 0 and isNumber(g.lines[y][x - 1])) {
                sum += g.getNumber(y, x - 1);
                var n = g.getNumber(y, x - 1);
                sum += n;
                if (char == 42 and n != 0) {
                    // print("n - {d} - {d}\n", .{ n, adjasentNumbers });
                    adjasentNumbers += 1;
                    gs = gs * n;
                }
            }

            if (x < line.len - 1 and isNumber(g.lines[y][x + 1])) {
                var n = g.getNumber(y, x + 1);
                sum += n;
                if (char == 42 and n != 0) {
                    // print("n - {d} - {d}\n", .{ n, adjasentNumbers });
                    adjasentNumbers += 1;
                    gs = gs * n;
                }
            }

            print("small sum - {d} - {d}\n", .{ adjasentNumbers, gs });
            if (adjasentNumbers == 2) {
                gearSum += gs;
            }
        }
    }

    print("Gear Sum - {d}\n", .{gearSum});
    print("Sum - {d}\n", .{sum});
    print("Time - {any}ms", .{std.time.milliTimestamp() - start});
}
