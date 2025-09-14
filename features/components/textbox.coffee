import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 30,
  text: "",
  textSize: 1024,
  editMode: false
};

@{Component('2d'), defaults}
function TextBox(
  @props
)
  @text = &(^"#{@props.text}\0")

function TextBox::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  
  result = GuiTextBoxWrapper rect, @text, @props.textSize, @props.editMode
  
  if result
    @props.editMode = !@props.editMode

  newText = *(@text).toString()
  if newText != @props.text
    @props.text = newText
    @emit 'change', newText

  free rect

export { TextBox }