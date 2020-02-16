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
