open Jest;


describe("Robot", () => {
  open Robot;
  open Table;
  open Expect;
  
  let table = Table.create(5);

  test("place", () => {  
    let robot = Robot.create();
    let expected: option(state) = Some({ 
      x: 1, y: 2, direction: NORTH, table: { x: 4, y: 4 }
    });

    let result = Robot.play(table, robot, [PLACE(1, 2, NORTH)]);
    expect(result) |> toEqual(expected);
  });

  test("place off board", () => {  
    let robot = Robot.create();
    let expected: option(state) = None;

    let result = Robot.play(table, robot, [PLACE(5, 6, NORTH)]);
    expect(result) |> toEqual(expected);
  });

  test("move", () => {  
    let robot = Robot.create();
    let expected: option(state) = Some({ 
      x: 1, y: 3, direction: NORTH, table: { x: 4, y: 4 }
    });

    let result = Robot.play(table, robot, [PLACE(1, 2, NORTH), MOVE]);
    expect(result) |> toEqual(expected);
  });

  test("move off board", () => {  
    let robot = Robot.create();
    let expected: option(state) = Some({ 
      x: 1, y: 4, direction: NORTH, table: { x: 4, y: 4 }
    });

    let result = Robot.play(table, robot, [PLACE(1, 2, NORTH), MOVE, MOVE, MOVE, MOVE]);
    expect(result) |> toEqual(expected);
  });

  test("left", () => {
    let robot = Robot.create();
    let expected: option(state) = Some({ 
      x: 1, y: 2, direction: WEST, table: { x: 4, y: 4 }
    });

    let result = Robot.play(table, robot, [PLACE(1, 2, NORTH), LEFT]);
    expect(result) |> toEqual(expected);
  });

  test("right", () => {
    let robot = Robot.create();
    let expected: option(state) = Some({ 
      x: 1, y: 2, direction: EAST, table: { x: 4, y: 4 }
    });

    let result = Robot.play(table, robot, [PLACE(1, 2, NORTH), RIGHT]);
    expect(result) |> toEqual(expected);
  });
});