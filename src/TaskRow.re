open Revery;
open Revery.UI;
open Revery.UI.Components;

let make = (~task: TimeTracker.task, ()) => {
  <View style=Styles.taskRow>
    <Text style=Styles.taskName text={task.name} />
    <Text style=Styles.taskText text={Utils.formatTime(task.elapsed)} />
  </View>;
};
