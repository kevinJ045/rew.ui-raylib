import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 200,
  text: ""
};

@{Component('2d'), defaults}
function Panel(
  @props
)

function Panel::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  GuiPanelWrapper rect, ^"#{@props.text}\0"
  FreePTRVal rect

export { Panel }