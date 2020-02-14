type task = {name: string};
type state = {
  newTaskName: string,
  tasks: list(task),
};

let init = (): state => {newTaskName: "", tasks: []};

type action =
  | NewTaskNameSet(string)
  | TaskAdded;

let reducer = (action, state) => {
  switch (action) {
  | NewTaskNameSet(name) => {...state, newTaskName: name}
  | TaskAdded =>
    let task = {name: state.newTaskName};
    {newTaskName: "", tasks: List.cons(task, state.tasks)};
  };
};
