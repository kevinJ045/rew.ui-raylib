import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  text: "",
  fontSize: 10,
  color: 0xFFFFFFFF,
}

@{Component('2d'), defaults}
function FlexText(
  @props
)

function FlexText::draw(time)
  { text, fontSize, color } = @props
  { x, y } = @_layout or @props
  drawer.drawText text, x, y, fontSize, color

export { FlexText }
