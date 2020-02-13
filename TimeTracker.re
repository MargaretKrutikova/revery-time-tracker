module TaskStatus = {
  type t =
    | NotStarted
    | Running(float)
    | Paused(float)
    | Done(float);

  let toStarted =
    fun
    | NotStarted => Running(0.0)
    | other => other;

  let toPaused =
    fun
    | Running(time) => Paused(time)
    | other => other;

  let toResumed =
    fun
    | Paused(time) => Running(time)
    | other => other;

  let toDone =
    fun
    | Running(time)
    | Paused(time) => Done(time)
    | other => other;

  let tick = (tick, status) =>
    switch (status) {
    | Running(time) => Running(time +. tick)
    | other => other
    };

  let isRunning =
    fun
    | Running(_) => true
    | _ => false;
};

module Task = {
  type t = {
    id: string,
    name: string,
    status: TaskStatus.t,
  };

  let make = (~name, ~id) => {id, name, status: NotStarted};
  let withStatus = (updateStatus, task) => {
    ...task,
    status: updateStatus(task.status),
  };
};

module State = {
  type t = {
    newTaskName: string,
    tasks: list(Task.t),
  };

  let init = () => {newTaskName: "", tasks: []};

  let updateTaskById = (id, update, tasks) =>
    List.map((task: Task.t) => task.id == id ? update(task) : task, tasks);

  let updateTaskStatus = (id, updateStatus, state) => {
    ...state,
    tasks: updateTaskById(id, Task.withStatus(updateStatus), state.tasks),
  };

  let getRunningTask = state =>
    state.tasks |> List.find_opt((task: Task.t) => task.status |> TaskStatus.isRunning);

  type action =
    | NewTaskNameSet(string)
    | TaskAdded
    | Tick(float)
    | TaskStarted(string)
    | TaskPaused(string)
    | TaskResumed(string)
    | TaskDone(string)
    | TaskRemoved(string);

  let reducer = (action, state) => {
    switch (action) {
    | NewTaskNameSet(name) => {...state, newTaskName: name}
    | Tick(tick) =>
      switch (getRunningTask(state)) {
      | None => state
      | Some(task) => updateTaskStatus(task.id, TaskStatus.tick(tick), state)
      }
    | TaskAdded =>
      let task = Task.make(~id=state.newTaskName, ~name=state.newTaskName);
      {newTaskName: "", tasks: List.cons(task, state.tasks)};
    | TaskStarted(id) =>
      switch (getRunningTask(state)) {
        | None => updateTaskStatus(id, TaskStatus.toStarted, state)
        | Some(task) =>
          state |> updateTaskStatus(task.id, TaskStatus.toPaused)
                |> updateTaskStatus(id, TaskStatus.toStarted);
        }
    | TaskPaused(id) => updateTaskStatus(id, TaskStatus.toPaused, state)
    | TaskResumed(id) => switch (getRunningTask(state)) {
      | None => updateTaskStatus(id, TaskStatus.toResumed, state)
      | Some(task) =>
        state |> updateTaskStatus(task.id, TaskStatus.toPaused)
              |> updateTaskStatus(id, TaskStatus.toResumed);
      }
    | TaskDone(id) => updateTaskStatus(id, TaskStatus.toDone, state)
    | TaskRemoved(id) => {
        ...state,
        tasks: List.filter((task: Task.t) => task.id != id, state.tasks),
      }
    };
  };
};
