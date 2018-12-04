open Table;
open Robot;

let table = Table.create(5);
let robot = Robot.create(table);

Robot.play(robot, [
  PLACE(1, 2, NORTH),
  RIGHT,
  MOVE,
  MOVE,
  MOVE,
  MOVE,
  MOVE,
  REPORT,
]);