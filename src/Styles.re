open Revery;
open Revery.UI;

let taskList =
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

let taskRow =
  Style.[
    height(50),
    flexDirection(`Row),
    justifyContent(`SpaceAround),
    alignItems(`Center),
    backgroundColor(Color.rgb(0.86, 0.86, 0.86)),
    paddingHorizontal(15),
    marginBottom(1),
  ];

let taskText =
  Style.[
    fontSize(28),
    fontFamily("Roboto-Regular.ttf"),
    color(Colors.black),
  ];

let taskName = List.append(taskText, Style.[flexGrow(1)]);
