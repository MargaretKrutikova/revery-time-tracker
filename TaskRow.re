open Revery;
open Revery.UI;
open Revery.UI.Components;
open TimeTracker;

module Styles = {};

let statusToBgColor = fun
  | TaskStatus.Running(_) => Colors.green
  | NotStarted => Colors.gray
  | Paused(_) => Colors.orange
  | Done(_)  => Colors.blue;

let make = (~task: TimeTracker.Task.t, ~dispatch, ()) => {
  let statusString =
    switch (task.status) {
      | Running(time)
      | Paused(time)
      | Done(time)  => time |> string_of_float
      | NotStarted => "Not Started"
    };
  <View style=Style.[border(~width=3, ~color=Colors.black),
  height(50),
  width(400),
  flexDirection(`Row),
  alignItems(`Center),
  justifyContent(`SpaceBetween),
  backgroundColor(statusToBgColor(task.status)),
  ]>
  <AppButton label="x" onClick={_ => dispatch(State.TaskRemoved(task.id))} />

  <View >
    <Text
      style=Style.[
        fontFamily("Roboto-Regular.ttf"),
        fontSize(16),
        lineHeight(20.0),
        color(Colors.black)
      ]
      text={task.name}
    />
    </View>
    <View>
    <Text
      style=Style.[
        fontFamily("Roboto-Regular.ttf"),
        fontSize(12),
        lineHeight(20.0),
      ]
      text={statusString}
    />
    </View>

{
  switch (task.status) {
    | Running(time) =>
      <AppButton label="Pause" onClick={_ => dispatch(TaskPaused(task.id))} />
    | NotStarted =>
    <AppButton label="Start" onClick={_ => dispatch(TaskStarted(task.id))} />
    | Paused(time) =>
    <AppButton label="Resume" onClick={_ => dispatch(TaskResumed(task.id))} />
    | _ => <View />
  }

}
{
  switch (task.status) {
    | NotStarted | Done(_) => <View />
    | other =>
      <AppButton label="Done" onClick={_ => dispatch(TaskDone(task.id))} />
  }
}

  </View>;
};
