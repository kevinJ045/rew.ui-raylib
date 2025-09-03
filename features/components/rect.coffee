import { Component, DrawFunction } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

@{Component('2d')}
function Rectangle(
  @x, @y,
  @w, @h,
  @color
)

function Rectangle::draw(time)
  DrawRectangle @x, @y, @w, @h, @color or 0xFFFF0000

export { Rectangle }