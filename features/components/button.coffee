import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 100,
  h: 40,
  text: ""
};

@{Component('2d'), defaults}
function Button(
  @props
)

function Button::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  GuiButtonWrapper rect, ^"#{@props.text}\0"
  FreePTRVal rect

export { Button }