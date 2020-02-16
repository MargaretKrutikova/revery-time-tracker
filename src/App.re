open Revery;
open Revery.UI;
open Revery.UI.Components;

let init = app => {
  let _ = Revery.Log.listen((_, msg) => print_endline("LOG: " ++ msg));

  let win = App.createWindow(app, "Time tracker");

  let containerStyle =
    Style.[
      position(`Absolute),
      alignItems(`Center),
      justifyContent(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
    ];

  let text =
    Style.[
      fontSize(28),
      fontFamily("Roboto-Regular.ttf"),
      color(Colors.black),
    ];

  let element =
    <View style=containerStyle> <Text style=text text="Hello world" /> </View>;
  let _ = UI.start(win, element);
  ();
};

App.start(init);
