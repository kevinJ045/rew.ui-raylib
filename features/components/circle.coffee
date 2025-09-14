import { Component } from "./base.coffee";
import { CreateVector2, CreateColor } from "../ffi/raylib.coffee"

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  radius: 50,
  color: { r: 255, g: 255, b: 255, a: 255 }
};

@{Component('2d'), defaults}
function Circle(
  @props
)

function Circle::draw(time, abs_pos)
  center = CreateVector2 abs_pos.x, abs_pos.y
  color = CreateColor @props.color.r, @props.color.g, @props.color.b, @props.color.a
  DrawCircleVWrapper center.ptr, @props.radius, color.ptr
  FreePTRVal center.ptr
  FreePTRVal color.ptr

export { Circle }