open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  let container =
    Style.[
      paddingHorizontal(20),
      paddingVertical(20),
      alignItems(`Stretch),
      flexGrow(1),
    ];

  let input =
    Style.[
      fontSize(24),
      border(~width=0, ~color=Colors.transparentWhite),
      borderBottom(~width=1, ~color=Colors.black),
      marginBottom(15),
      minWidth(500),
    ];
};

let%component make = () => {
  let%hook (state, dispatch) =
    Hooks.reducer(~initialState=TimeTracker.init(), TimeTracker.reducer);

  let onKeyDown = (event: NodeEvents.keyEventParams) =>
    if (event.keycode == 13) {
      dispatch(TaskAdded);
    };

  <View style=Styles.container>
    <View>
      <Input
        placeholder="Task name"
        onChange={(value, _) => {dispatch(NewTaskNameSet(value))}}
        value={state.newTaskName}
        style=Styles.input
        onKeyDown
      />
    </View>
    <Ticker onTick={t => dispatch(Tick(t |> Time.toFloatSeconds))}>
      <View>
        {state.tasks
         |> List.rev
         |> List.map((task: TimeTracker.task) => <TaskRow task />)
         |> React.listToElement}
      </View>
    </Ticker>
  </View>;
};
