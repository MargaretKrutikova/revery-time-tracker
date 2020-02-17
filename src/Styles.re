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
    minWidth(400),
  ];

let taskRow =
  Style.[
    height(50),
    justifyContent(`Center),
    backgroundColor(Color.rgb(0.86, 0.86, 0.86)),
    paddingHorizontal(15),
    marginBottom(1),
  ];

let taskText =
  Style.[
    fontSize(22),
    fontFamily("Roboto-Regular.ttf"),
    color(Colors.black),
  ];
