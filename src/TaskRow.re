open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  let container =
    Style.[
      height(50),
      justifyContent(`Center),
      backgroundColor(Color.rgb(0.86, 0.86, 0.86)),
      paddingHorizontal(15),
      marginBottom(1),
    ];

  let text =
    Style.[
      fontSize(22),
      fontFamily("Roboto-Regular.ttf"),
      color(Colors.black),
    ];
};

let make = (~task: TimeTracker.task, ()) => {
  <View style=Styles.container>
    <View> <Text style=Styles.text text={task.name} /> </View>
  </View>;
};
