open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {};

let%component make = () => {
  let%hook (state, dispatch) =
    Hooks.reducer(
      ~initialState=TimeTracker.State.init(),
      TimeTracker.State.reducer,
    );

  let input =
    Style.[
      fontSize(22),
      border(~width=0, ~color=Colors.transparentWhite),
      width(4000),
    ];

  let onKeyDown = (event: NodeEvents.keyEventParams) =>
    if (event.keycode == 13) {
      dispatch(TaskAdded);
    };

  <View>
    <View>
      <Input
        placeholder="Task name"
        onChange={(value, _) => {dispatch(NewTaskNameSet(value))}}
        value={state.newTaskName}
        style=input
        onKeyDown
      />
    </View>
    <Ticker onTick={t => dispatch(Tick(t |> Time.toFloatSeconds))}>
      <ScrollView style=Style.[height(400), paddingHorizontal(20)]>
        {state.tasks
         |> List.rev
         |> List.map((task: TimeTracker.Task.t) => <TaskRow task dispatch />)
         |> React.listToElement}
      </ScrollView>
    </Ticker>
  </View>;
};
