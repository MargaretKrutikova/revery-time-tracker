open Revery;
open Revery.UI;
open Revery.UI.Components;

let%component make = () => {
  let%hook (state, dispatch) =
    Hooks.reducer(~initialState=TimeTracker.init(), TimeTracker.reducer);

  let onKeyDown = (event: NodeEvents.keyEventParams) =>
    if (event.keycode == 13) {
      dispatch(TaskAdded);
    };

  <View style=Styles.taskList>
    <View>
      <Input
        placeholder="Task name"
        onChange={(value, _) => {dispatch(NewTaskNameSet(value))}}
        value={state.newTaskName}
        style=Styles.input
        onKeyDown
      />
    </View>
    <View>
      {state.tasks
       |> List.rev
       |> List.map((task: TimeTracker.task) => <TaskRow task />)
       |> React.listToElement}
    </View>
  </View>;
};
