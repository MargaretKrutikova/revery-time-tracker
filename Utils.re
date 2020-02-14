open Revery;

let getPathToAsset = assetName =>
  Environment.getExecutingDirectory() ++ assetName;

type division = {
  remainder: int,
  quotient: int,
};

let divide = (x, y) => {remainder: x mod y, quotient: x / y};

let prependZero = value => (value < 10 ? "0" : "") ++ string_of_int(value);

let formatTime = (seconds: float) => {
  let hour = divide(seconds |> int_of_float, 60 * 60);
  let min = divide(hour.remainder, 60);
  let sec = min.remainder;
  let secStr = prependZero(sec);

  if (hour.quotient == 0) {
    Printf.sprintf("%d:%s", min.quotient, secStr);
  } else {
    Printf.sprintf("%d:%d:%s", hour.quotient, min.quotient, secStr);
  };
};
