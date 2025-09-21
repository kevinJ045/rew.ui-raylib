import { Component } from "./base.coffee";
import { CreateColor } from "../ffi/raylib.coffee"

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  text: "",
  fontSize: 20,
  color: { r: 255, g: 255, b: 255, a: 255 }
};

@{Component('2d'), defaults}
function Text(
  @props
)

function Text::draw(time)
  color = CreateColor @props.color.r, @props.color.g, @props.color.b, @props.color.a
  DrawText ^"#{@props.text}\0", @x, @y, @props.fontSize, color.ptr
  FreePTRVal color.ptr

export { Text }