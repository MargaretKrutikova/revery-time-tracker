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

  let scrollView = Style.[alignItems(`Stretch), flexGrow(1)];
};

let%component make = (~window, ()) => {
  let%hook (state, dispatch) =
    Hooks.reducer(
      ~initialState=TimeTracker.State.init(),
      TimeTracker.State.reducer,
    );

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
    <ScrollView style=Styles.scrollView>
      <Ticker onTick={t => dispatch(Tick(t |> Time.toFloatSeconds))}>
        {state.tasks
         |> List.rev
         |> List.map((task: TimeTracker.Task.t) =>
              <TaskRow window task dispatch />
            )
         |> React.listToElement}
      </Ticker>
    </ScrollView>
  </View>;
};
