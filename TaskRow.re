open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {};

let make = (~task: TimeTracker.Task.t, ()) => {
  <View style=Style.[border(~width=3, ~color=Colors.black), height(50)]>
    <Text
      style=Style.[
        fontFamily("Roboto-Regular.ttf"),
        fontSize(16),
        lineHeight(20.0),
      ]
      text={task.name}
    />
  </View>;
};
