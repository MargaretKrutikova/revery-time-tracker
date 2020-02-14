open Revery;
open Revery.UI;
open Revery.UI.Components;

let make = (~asset, ~onClick=?, ~width=40, ~height=40, ()) => {
  <Clickable ?onClick>
    <Image src={Utils.getPathToAsset(asset)} width height />
  </Clickable>;
};
