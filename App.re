open Revery;
open Revery.UI;
open Revery.UI.Components;

let init = app => {
  let _ = Revery.Log.listen((_, msg) => print_endline("LOG: " ++ msg));

  let win = App.createWindow(app, "Time tracker");

  let containerStyle =
    Style.[
      position(`Absolute),
      alignItems(`Stretch),
      bottom(0),
      top(0),
      left(0),
      right(0),
    ];

  let element = <View style=containerStyle> <TaskList window=win /> </View>;
  let _ = UI.start(win, element);
  ();
};

App.start(init);
