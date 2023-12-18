const std = @import("std");

const Node = struct {
    value: ?f64 = null,
    operation: ?Operations = null,
    left: ?*Node = null,
    right: ?*Node = null,

    const Operations = enum(u8) { plus = 43, minus = 45, multiple = 42, devide = 47 };

    fn init(allocator: std.mem.Allocator) !*Node {
        var t = try allocator.create(Node);
        t.operation = null;
        t.value = null;
        t.left = null;
        t.right = null;

        return t;
    }

    fn charToOperation(c: u8, allocator: std.mem.Allocator) NodeErrors!*Node {
        var n: *Node = Node.init(allocator) catch |err| {
            std.debug.print("failed to create node - {any}\n", .{err});
            return NodeErrors.WrongOperation;
        };

        return switch (c) {
            42 => {
                n.operation = Operations.multiple;
                return n;
            },
            43 => {
                n.operation = Operations.plus;
                return n;
            },
            47 => {
                n.operation = Operations.devide;
                return n;
            },
            45 => {
                n.operation = Operations.minus;
                return n;
            },
            else => NodeErrors.UnsupportedOperation,
        };
    }

    const NodeErrors = error{ MissingLeftOperation, MissingRightOperation, WrongOperation, UnsupportedOperation };

    fn getValue(self: *Node) NodeErrors!f64 {
        if (self.value) |val| {
            return val;
        }

        const l = if (self.left) |val| try val.getValue() else return NodeErrors.MissingLeftOperation;
        const r = if (self.right) |val| try val.getValue() else return NodeErrors.MissingRightOperation;

        if (self.operation == null) {
            return NodeErrors.WrongOperation;
        }

        return switch (self.operation.?) {
            Operations.plus => l + r,
            Operations.minus => l - r,
            Operations.multiple => l * r,
            Operations.devide => l / r,
        };
    }

    fn print(self: *Node) void {
        if (self.value != null) {
            std.debug.print("Value - {?d}\n", .{self.value});
        }
        if (self.operation != null) {
            std.debug.print("Operation - {?any}\n", .{self.operation});
        }

        if (self.left) |l| {
            std.debug.print("printing left\n", .{});
            l.print();
        }

        if (self.right) |r| {
            std.debug.print("printing right\n", .{});
            r.print();
        }

        return;
    }

    fn destroy(self: *Node, allocator: std.mem.Allocator) void {
        if (self.left) |l| {
            l.destroy(allocator);
        }

        if (self.right) |r| {
            r.destroy(allocator);
        }

        allocator.destroy(self);

        return;
    }
};

pub fn main() !void {
    const exp = "134-4";

    var gp = std.heap.GeneralPurposeAllocator(.{ .safety = true }){};
    defer _ = gp.deinit();
    const allocator = gp.allocator();

    var head: *Node = try Node.init(allocator);

    var iteration: f64 = 1;
    for (exp) |char| {
        switch (char) {
            48...57 => { //numbers
                if (head.operation != null) {
                    var temp = try Node.init(allocator);
                    head = temp;
                }

                var f: f64 = @floatFromInt(char);
                head.value = if (head.value) |v| (v * 10) + (f - 48) else (f - 48) * iteration;
                iteration += 1;
            },
            42, 45, 47, 43 => { // operations
                var temp = Node.charToOperation(char, allocator) catch |err| {
                    std.debug.print("failed to read in operation - {c}- {any}\n", .{ char, err });
                    return;
                };

                if (head.left != null) {
                    temp.left = head;
                    head = temp;
                } else if (head.right != null) {
                    temp.right = head;
                    head = temp;
                }

                head.left = temp;

                // used to track numbers while parsing expression
                iteration = 1;
            },
            else => {
                iteration = 1;
            },
        }
    }

    head.print();
    std.debug.print("Result - {!d}\n", .{head.getValue()});

    head.destroy(allocator);
}
