import { Component } from "./base.coffee";
import { calculateLayout } from "../layout.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  text: "",
  fontSize: 10,
  color: 0xFFFFFFFF,
  spacing: 1
}

@{Component('2d'), defaults}
function FlexText(
  @props
)

function FlexText::draw(time)
  { text, fontSize, spacing, color } = @props
  calculateLayout this, this.parent
  { x, y } = @_layout

  font = GetFontDefaultWrapper()
  pos = CreateVector2 x || 0, y || 0

  tb = ^"#{text}\0"
  sizePtr = MeasureTextExWrapper font, tb, fontSize, spacing
  size = *sizePtr.as({ x: 'f32', y: 'f32' })
  @width = size.x
  @height = size.x

  DrawTextExWrapper font, tb, pos, fontSize, spacing, color

  FreePTRVal font
  FreePTRVal pos

export { FlexText }
