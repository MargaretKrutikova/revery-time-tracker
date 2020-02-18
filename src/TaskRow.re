open Revery;
open Revery.UI;
open Revery.UI.Components;

let make = (~task: TimeTracker.task, ()) => {
  <View style=Styles.taskRow>
    <Text style=Styles.taskText text={task.name} />
  </View>;
};
