type task = {
  name: string,
  elapsed: float,
};

type state = {
  newTaskName: string,
  tasks: list(task),
};

let init = () => {newTaskName: "", tasks: []};

type action =
  | NewTaskNameSet(string)
  | TaskAdded
  | Tick(float);

let reducer = (action, state) => {
  switch (action) {
  | NewTaskNameSet(name) => {...state, newTaskName: name}
  | TaskAdded =>
    let task = {name: state.newTaskName, elapsed: 0.0};
    {newTaskName: "", tasks: List.cons(task, state.tasks)};
  | Tick(tick) =>
    let tasks =
      state.tasks
      |> List.map((task: task) => {...task, elapsed: task.elapsed +. tick});
    {...state, tasks};
  };
};
