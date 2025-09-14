import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 100,
  h: 100,
  text: ""
};

@{Component('2d'), defaults}
function GroupBox(
  @props
)

function GroupBox::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  GuiGroupBoxWrapper rect, ^"#{@props.text}\0"
  FreePTRVal rect

export { GroupBox }