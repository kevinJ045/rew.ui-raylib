import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 20,
  textLeft: "",
  textRight: "",
  value: 0,
  min: 0.0,
  max: 1.0
};

@{Component('2d'), defaults}
function ProgressBar(
  @props
)

function ProgressBar::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  val = &(Math.max(Math.min(0.99999, @props.value), 0.00), 'f32')
  GuiProgressBarWrapper rect, ^"#{@props.textLeft}\0", ^"#{@props.textRight}\0", val, @props.min, @props.max
  FreePTRVal rect

export { ProgressBar }