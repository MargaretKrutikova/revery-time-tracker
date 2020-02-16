open Revery;
open Revery.UI;
open Revery.UI.Components;

let make = (~task: Task.t, ~window: Window.t, ~dispatch, ()) => {
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
    dispatch(TimeTracker.TaskDone(task.id));
  };

  <View style={Styles.taskRow(task.status)}>
    <Text style=Styles.taskName text={task.name} />
    <View> <Text style=Styles.taskTime text=time /> </View>
    <View style=Styles.taskActions>
      {switch (task.status) {
       | Running(_) =>
         <IconButton
           asset="pause.png"
           onClick={_ => dispatch(TaskPaused(task.id))}
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
        onClick={_ => dispatch(TaskRemoved(task.id))}
      />
    </View>
  </View>;
};
