open Revery;
open Revery.UI;
open Revery.UI.Components;
open TimeTracker;

module Styles = {};

let statusToBgColor =
  fun
  | TaskStatus.Running(_) => Color.rgb(0.71, 0.84, 0.66)
  | NotStarted => Color.rgb(0.86, 0.86, 0.86)
  | Paused(_) => Color.rgb(1.0, 0.9, 0.6)
  | Done(_) => Color.rgb(197.0 /. 255.0, 220.0 /. 255.0, 251.0 /. 255.0);

let showAlert = (window: Window.t) => {
  Sdl2.MessageBox.showSimple(
    Warning,
    "Task can't be set to done",
    "The task has not been started and can't be moved to done.",
    Some(window.sdlWindow),
  );
};

let make = (~task: TimeTracker.Task.t, ~window, ~dispatch, ()) => {
  let statusString =
    switch (task.status) {
    | Running(time)
    | Paused(time)
    | Done(time) => time |> Utils.formatTime
    | _ => ""
    };

  <View
    style=Style.[
      height(50),
      flexDirection(`Row),
      alignItems(`Center),
      justifyContent(`SpaceBetween),
      backgroundColor(statusToBgColor(task.status)),
      paddingHorizontal(15),
      marginBottom(1),
    ]>
    <View>
      <Text
        style=Style.[
          fontFamily("Roboto-Regular.ttf"),
          fontSize(16),
          color(Colors.black),
        ]
        text={task.name}
      />
    </View>
    <View>
      <Text
        style=Style.[
          fontFamily("Roboto-Regular.ttf"),
          fontSize(24),
          color(Colors.black),
        ]
        text=statusString
      />
    </View>
    <View
      style=Style.[
        width(125),
        flexDirection(`Row),
        alignItems(`Center),
        justifyContent(`FlexEnd),
      ]>
      {switch (task.status) {
       | Running(_) =>
         <IconButton
           asset="pause.png"
           onClick={_ => dispatch(State.TaskPaused(task.id))}
         />
       | NotStarted =>
         <IconButton
           asset="play.png"
           onClick={_ => dispatch(TaskStarted(task.id))}
         />

       | Paused(_) =>
         <IconButton
           asset="play.png"
           onClick={_ => dispatch(TaskResumed(task.id))}
         />
       | _ => <View />
       }}
      <IconButton
        asset="done.png"
        onClick={_ => {
          showAlert(window);
          dispatch(State.TaskDone(task.id));
        }}
      />
      <IconButton
        asset="remove.png"
        width=25
        height=25
        onClick={_ => dispatch(State.TaskRemoved(task.id))}
      />
    </View>
  </View>;
};
