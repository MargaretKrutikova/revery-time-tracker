open Revery;
open Revery.UI;

let statusToBgColor =
  fun
  | TaskStatus.Running(_) => Color.rgb(0.71, 0.84, 0.66)
  | NotStarted => Color.rgb(0.86, 0.86, 0.86)
  | Paused(_) => Color.rgb(1.0, 0.9, 0.6)
  | Done(_) => Color.rgb(0.77, 0.86, 0.98);

let taskRow = status =>
  Style.[
    height(60),
    flexDirection(`Row),
    alignItems(`Center),
    justifyContent(`SpaceBetween),
    backgroundColor(statusToBgColor(status)),
    paddingHorizontal(15),
    marginBottom(1),
  ];

let text =
  Style.[
    fontSize(30),
    fontFamily("Roboto-Regular.ttf"),
    color(Colors.black),
  ];
let taskName = List.append(Style.[flexGrow(1)], text);
let taskTime = text;

let taskActions =
  Style.[
    width(125),
    flexDirection(`Row),
    alignItems(`Center),
    justifyContent(`FlexEnd),
  ];

let taskList = Style.[padding(20), alignItems(`Stretch), flexGrow(1)];
let input =
  Style.[
    fontSize(24),
    border(~width=0, ~color=Colors.transparentWhite),
    borderBottom(~width=1, ~color=Colors.black),
    marginBottom(15),
    minWidth(500),
  ];

let scrollView = Style.[alignItems(`Stretch), flexGrow(1)];
