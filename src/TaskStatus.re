type t =
  | NotStarted
  | Running(float)
  | Paused(float)
  | Done(float);

// function per each state transition
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

// define business rules
let toDone =
  fun
  | Running(time)
  | Paused(time) => Done(time)
  | other => other;

let tick = (elapsed, status) =>
  switch (status) {
  | Running(time) => Running(time +. elapsed)
  | other => other
  };

// utility functions
let isRunning =
  fun
  | Running(_) => true
  | _ => false;
