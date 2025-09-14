import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 20,
  text: ""
};

@{Component('2d'), defaults}
function StatusBar(
  @props
)

function StatusBar::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  GuiStatusBarWrapper rect, ^"#{@props.text}\0"
  FreePTRVal rect

export { StatusBar }