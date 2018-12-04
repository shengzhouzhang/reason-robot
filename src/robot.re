open Table;

type direction = NORTH | SOUTH | WEST | EAST;
type action = PLACE(int, int, direction) | LEFT | RIGHT | MOVE | REPORT;

type state = {
  x: int,
  y: int,
  direction: direction,
};

module Robot = {

  type robot = {
    state: ref(option(state)),
    table: table,
  };

  let place = (prevState: option(state), x: int, y: int, direction: direction, table: table): option(state) =>
    switch(Table.isInside(table, x, y)) {
    | true => Some({ x: x, y: y, direction: direction });
    | false => prevState;
    };

  let left = (prevState: state): state => 
    switch(prevState.direction) {
    | NORTH => { ...prevState, direction: WEST }
    | SOUTH => { ...prevState, direction: EAST }
    | WEST => { ...prevState, direction: SOUTH }
    | EAST => { ...prevState, direction: NORTH }
    };

  let right = (prevState: state): state => 
    switch(prevState.direction) {
    | NORTH => { ...prevState, direction: EAST }
    | SOUTH => { ...prevState, direction: WEST }
    | WEST => { ...prevState, direction: NORTH }
    | EAST => { ...prevState, direction: SOUTH }
    };

  let move = (prevState: state, table: table): state => {
    let nextState = switch(prevState.direction) {
      | NORTH => { ...prevState, y: prevState.y + 1 }
      | SOUTH => { ...prevState, y: prevState.y - 1 }
      | WEST => { ...prevState, x: prevState.x - 1 }
      | EAST => { ...prevState, x: prevState.x + 1 }
      };
    
    switch(Table.isInside(table, nextState.x, nextState.y)) {
      | true => nextState;
      | false => prevState;
      };
  }
    
  let report = (prevState: option(state)) => {
    Js.log(prevState);
    prevState;
  }

  let reducer = (table: table) => 
    (state: option(state), action: action): option(state) =>
      switch (state, action) {
      | (_, PLACE(x, y, direction)) => place(state, x, y, direction, table)
      | (_, REPORT) => report(state)
      | (Some(prevState), LEFT) => Some(left(prevState))
      | (Some(prevState), RIGHT) => Some(right(prevState))
      | (Some(prevState), MOVE) => Some(move(prevState, table))
      | _ => state
      };

  let play = (robot: robot, actions: list('action)): option(state) =>
    List.fold_left(reducer(robot.table), robot.state^, actions);

  let create = (table: table): robot => { state: ref(None), table: table };
}