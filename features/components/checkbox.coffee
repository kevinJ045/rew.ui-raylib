import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 20,
  h: 20,
  text: "",
  checked: false
};

@{Component('2d'), defaults}
function CheckBox(
  @props
)
  @checked = &(@props.checked)

function CheckBox::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  result = GuiCheckBoxWrapper rect, ^"#{@props.text}\0", @checked
  checked = *(@checked)
  if @props.checked != checked
    @props.checked = checked
    @emit 'change', checked
  FreePTRVal rect

export { CheckBox }