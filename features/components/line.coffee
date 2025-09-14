import { Component } from "./base.coffee";
import { CreateVector2, CreateColor } from "../ffi/raylib.coffee"

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  x2: 100,
  y2: 100,
  color: { r: 255, g: 255, b: 255, a: 255 }
};

@{Component('2d'), defaults}
function Line(
  @props
)

function Line::draw(time, abs_pos)
  startPos = CreateVector2 abs_pos.x, abs_pos.y
  endPos = CreateVector2 abs_pos.x + @props.x2, abs_pos.y + @props.y2
  color = CreateColor @props.color.r, @props.color.g, @props.color.b, @props.color.a
  DrawLineVWrapper startPos.ptr, endPos.ptr, color.ptr
  FreePTRVal startPos.ptr
  FreePTRVal endPos.ptr
  FreePTRVal color.ptr

export { Line }