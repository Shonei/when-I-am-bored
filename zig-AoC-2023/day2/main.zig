const std = @import("std");
const print = std.debug.print;

const gameSet = struct { cudeColor: []const u8, val: i32 };

pub fn main() !void {
    var start = std.time.milliTimestamp();

    var lines = std.mem.split(u8, @embedFile("input.txt"), "\n");

    const maxBlue: i32 = 14;
    const maxRed: i32 = 12;
    const maxGreen: i32 = 13;

    var possibleGameSum: i32 = 0;
    var minCubePower: i128 = 0;

    while (lines.next()) |line| {
        // print("Line - {s}\n", .{line});
        var gameNumber: i32 = 0;
        var index: u64 = 0;

        // find game number
        for (5..line.len) |i| {
            if (line[i] == 58) { // 58 is the unicode for :
                gameNumber = std.fmt.parseInt(i32, line[5..i], 10) catch {
                    print("failed to parse int {any}\n", .{line[5..i]});
                    return;
                };

                // print("Found game = {d}", .{gameNumber});
                index = i;
                break;
            }
        }

        // a game looks liekthis 'Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green'
        // once we have the game the index poits at the ganem number so int he exmple at 5
        // we add +2 so we get past the :<space> and end up at the first set
        var gameRecord = std.mem.split(u8, line[index + 2 .. line.len], " ");

        var blueCount: i32 = 0;
        var greenCount: i32 = 0;
        var redCount: i32 = 0;
        var isGamePossible = true;

        var blueMinCount: i32 = 0;
        var greenMinCount: i32 = 0;
        var redMinCount: i32 = 0;

        while (gameRecord.next()) |n| {
            var numberOfCubes = std.fmt.parseInt(i32, n, 10) catch {
                print("failed to parse int {?s}\n", .{n});
                return;
            };
            var cubeColor = gameRecord.next();

            // cubeColor looks like this red, or if there is , there is a \r on windonws which is where I am writing this on
            switch (cubeColor.?[0]) {
                103 => { // g
                    greenCount += numberOfCubes;
                },
                98 => { // b
                    blueCount += numberOfCubes;
                },
                114 => { // r
                    redCount += numberOfCubes;
                },
                else => {},
            }

            var lastChar = cubeColor.?[cubeColor.?.len - 1];
            if (lastChar != 44) { // , means he hand of dice continues
                if (blueCount > maxBlue) {
                    isGamePossible = false;
                } else if (greenCount > maxGreen) {
                    isGamePossible = false;
                } else if (redCount > maxRed) {
                    isGamePossible = false;
                }

                if (blueMinCount < blueCount) {
                    blueMinCount = blueCount;
                }
                if (greenMinCount < greenCount) {
                    greenMinCount = greenCount;
                }
                if (redMinCount < redCount) {
                    redMinCount = redCount;
                }

                //reset counters
                blueCount = 0;
                greenCount = 0;
                redCount = 0;
            }
        }

        minCubePower += redMinCount * greenMinCount * blueMinCount;
        blueMinCount = 0;
        greenMinCount = 0;
        redMinCount = 0;

        if (isGamePossible) {
            possibleGameSum += gameNumber;
            // print("Game - {d}\n", .{gameNumber});
        }
    }

    print("minimum cube power = {d}\n", .{minCubePower});
    print("sum of possible games = {d}\n", .{possibleGameSum});
    print("Time - {any}ms", .{std.time.milliTimestamp() - start});
}
