import { Component, DrawFunction } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

size = 30
color = 0xFF000000

@{Component('2d')}
function Text(
  @text,
  @x,
  @y,
  @color = color,
  @size = size
)

function Text::draw(time)
  DrawText ^"#{@text}\0", @x, @y, @size, @color

function Text.setStyle(_size = size, _color = color)
  size = _size;
  color = _color;

export { Text }