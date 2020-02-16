open Revery;
open Revery.UI;
open Revery.UI.Components;
open TimeTracker;

module Styles = {
  let statusToBgColor =
    fun
    | TaskStatus.Running(_) => Color.rgb(0.71, 0.84, 0.66)
    | NotStarted => Color.rgb(0.86, 0.86, 0.86)
    | Paused(_) => Color.rgb(1.0, 0.9, 0.6)
    | Done(_) => Color.rgb(0.77, 0.86, 0.98);

  let container = status =>
    Style.[
      height(60),
      flexDirection(`Row),
      alignItems(`Center),
      justifyContent(`SpaceBetween),
      backgroundColor(statusToBgColor(status)),
      paddingHorizontal(15),
      marginBottom(1),
    ];

  let text =
    Style.[
      fontSize(30),
      fontFamily("Roboto-Regular.ttf"),
      color(Colors.black),
    ];
  let taskName = List.append(Style.[flexGrow(1)], text);
  let time = text;

  let actions =
    Style.[
      width(125),
      flexDirection(`Row),
      alignItems(`Center),
      justifyContent(`FlexEnd),
    ];
};

let make = (~task: TimeTracker.Task.t, ~window: Window.t, ~dispatch, ()) => {
  let time =
    switch (task.status) {
    | Running(time)
    | Paused(time)
    | Done(time) => time |> Utils.formatTime
    | _ => ""
    };

  let showTaskCantBeDoneAlert = () => {
    Sdl2.MessageBox.showSimple(
      Warning,
      "Task can't be set to done",
      "Task must be started in order to be moved to done.",
      Some(window.sdlWindow),
    );
  };

  let handleTaskDone = _ => {
    switch (task.status) {
    | NotStarted => showTaskCantBeDoneAlert()
    | _ => ignore()
    };
    dispatch(State.TaskDone(task.id));
  };

  <View style={Styles.container(task.status)}>
    <Text style=Styles.taskName text={task.name} /> 
    <View> <Text style=Styles.time text=time /> </View>
    <View style=Styles.actions>
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
      <IconButton asset="done.png" onClick=handleTaskDone />
      <IconButton
        asset="remove.png"
        width=25
        height=25
        onClick={_ => dispatch(State.TaskRemoved(task.id))}
      />
    </View>
  </View>;
};
