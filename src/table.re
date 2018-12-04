type table = { 
  x: int, 
  y: int,
};

let create = (size: int): table => { x: size - 1, y: size - 1 }
let isInside = (table: table, x: int, y: int) => table.x >= x && table.y >= y && x >= 0 && y >= 0;