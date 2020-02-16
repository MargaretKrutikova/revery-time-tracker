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
