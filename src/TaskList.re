open Revery;
open Revery.UI;
open Revery.UI.Components;

let%component make = (~window, ()) => {
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
    <ScrollView style=Styles.scrollView>
      <Ticker onTick={t => dispatch(Tick(t |> Time.toFloatSeconds))}>
        {state.tasks
         |> List.rev
         |> List.map((task: Task.t) => <TaskRow window task dispatch />)
         |> React.listToElement}
      </Ticker>
    </ScrollView>
  </View>;
};
