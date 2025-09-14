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
function Rect(
  @props
)

function Rect::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  DrawRectangleRoundedWrapper rect, @props.radius, @props.segments, @props.color
  DrawRectangleRoundedLinesExWrapper rect, @props.radius, @props.segments, @props.border, @props.color if @props.border
  FreePTRVal rect

export { Rect }