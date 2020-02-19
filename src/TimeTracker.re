type state = {
  newTaskName: string,
  tasks: list(Task.t),
};

let init = () => {newTaskName: "", tasks: []};

type action =
  | NewTaskNameSet(string)
  | TaskAdded
  | Tick(float)
  /* action for each task status transition */
  | TaskStarted(string)
  | TaskPaused(string)
  | TaskResumed(string)
  | TaskDone(string)
  | TaskRemoved(string);

/* utility functions */
let updateTaskById = (id, update, tasks) =>
  List.map((task: Task.t) => task.id == id ? update(task) : task, tasks);

let updateTaskStatus = (id, updateStatus, state) => {
  ...state,
  tasks: state.tasks |> updateTaskById(id, Task.withStatus(updateStatus)),
};

let removeTask = (id, state) => {
  ...state,
  tasks: state.tasks |> List.filter((task: Task.t) => task.id != id),
};

let getRunningTask = state =>
  state.tasks
  |> List.find_opt((task: Task.t) => task.status |> TaskStatus.isRunning);

let pauseRunningTask = state =>
  switch (getRunningTask(state)) {
  | None => state
  | Some(task) => state |> updateTaskStatus(task.id, TaskStatus.pause)
  };

let reducer = (action, state) => {
  switch (action) {
  | NewTaskNameSet(name) => {...state, newTaskName: name}

  | TaskStarted(id) =>
    state |> pauseRunningTask |> updateTaskStatus(id, TaskStatus.start)
  | TaskPaused(id) => state |> updateTaskStatus(id, TaskStatus.pause)
  | TaskResumed(id) =>
    state |> pauseRunningTask |> updateTaskStatus(id, TaskStatus.resume)
  | TaskDone(id) => state |> updateTaskStatus(id, TaskStatus.finish)
  | TaskRemoved(id) => state |> removeTask(id)

  | Tick(tick) =>
    switch (getRunningTask(state)) {
    | None => state
    | Some(task) => updateTaskStatus(task.id, TaskStatus.tick(tick), state)
    }
  | TaskAdded =>
    let task = Task.make(~id=state.newTaskName, ~name=state.newTaskName);
    {newTaskName: "", tasks: List.cons(task, state.tasks)};
  };
};
