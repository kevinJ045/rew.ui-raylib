import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 100,
  h: 100,
  color: 0xFFFFFFFF,
  radius: 0,
  segments: 0,
  border: 0
}

@{Component('2d'), defaults}
function FlexRect(
  @props
)

function FlexRect::draw(time)
  { color } = @props
  { x, y, width, height } = @_layout or @props
  rect = CreateRectangle x, y, width, height
  DrawRectangleRoundedWrapper rect, @props.radius, @props.segments, @props.color
  DrawRectangleRoundedLinesExWrapper rect, @props.radius, @props.segments, @props.border, @props.color if @props.border
  FreePTRVal rect

export { FlexRect }
