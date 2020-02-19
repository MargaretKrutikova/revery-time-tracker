type t =
  | NotStarted
  | Running(float)
  | Paused(float)
  | Done(float);

/* function per each state transition */
let start = status =>
  switch (status) {
  | NotStarted => Running(0.0)
  | other => other
  };

let pause =
  fun
  | Running(time) => Paused(time)
  | other => other;

let resume =
  fun
  | Paused(time) => Running(time)
  | other => other;

/* define business rules */
let finish =
  fun
  | Running(time)
  | Paused(time) => Done(time)
  | other => other;

let tick = (elapsed, status) =>
  switch (status) {
  | Running(time) => Running(time +. elapsed)
  | other => other
  };

 /* utility functions */
let isRunning =
  fun
  | Running(_) => true
  | _ => false;
