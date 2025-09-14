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
function LabelButton(
  @props
)

function LabelButton::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  result = GuiLabelButtonWrapper rect, ^"#{@props.text}\0"
  if result != 0
    if @props.onClick
      @props.onClick()
  FreePTRVal rect

export { LabelButton }