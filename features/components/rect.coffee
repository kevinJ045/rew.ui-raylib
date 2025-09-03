import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

@{Component('2d')}
function Rectangle(
  @x, @y,
  @w, @h,
  @color
)

function Rectangle::draw(time)
  pos = CreateVector2 @x, @y
  size = CreateVector2 @w, @h
  DrawRectangleVWrapper pos, size, @color or 0xFFFF0000
  FreePTRVal pos
  FreePTRVal size

function Rectangle::getRect()
  if @_current_rec
    return @_current_rec
  @_current_rec = CreateRectangle @x, @y, @w, @h
  @_current_rec

function Rectangle::freeRect()
  FreePTRVal @_current_rec
  @_current_rec = null;

export { Rectangle }