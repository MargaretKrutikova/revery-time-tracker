open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  let container =
    Style.[
      position(`Relative),
      justifyContent(`Center),
      alignItems(`Center),
      paddingVertical(5),
      paddingHorizontal(8),
      backgroundColor(Colors.coral),
      border(~width=2, ~color=Colors.black),
      borderRadius(2.0),
      flexGrow(0),
    ];
  let text =
    Style.[
      textWrap(TextWrapping.NoWrap),
      fontSize(14),
      fontFamily("Roboto-Regular.ttf"),
    ];
};

let make = (~label, ~onClick, ()) => {
  <Clickable onClick>
    <View style=Styles.container> <Text style=Styles.text text=label /> </View>
  </Clickable>;
};
