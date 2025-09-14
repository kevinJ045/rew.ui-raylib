import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 100,
  h: 40,
  items: [],
  active: 0,
  editMode: false
};

@{Component('2d'), defaults}
function Dropdown(
  @props
)
  @active = &(@props.active)

function Dropdown::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  text = @props.items.join(';')
  result = GuiDropdownBoxWrapper rect, ^"#{text}\0", @active, @props.editMode
  if result
    @props.editMode = !@props.editMode
  active = *(@active)
  if active != @props.active
    @props.active = active
    @emit 'change', active
  FreePTRVal rect

export { Dropdown }