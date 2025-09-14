import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 120,
  h: 30,
  text: "",
  value: 0,
  minValue: 0,
  maxValue: 100,
  editMode: false
};

@{Component('2d'), defaults}
function Spinner(
  @props
)
  # Create a buffer to hold the integer value.
  valueBuf = rew::ffi::buffer(4)
  valueBuf.writeInt32LE(@props.value, 0)

function Spinner::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  
  # The wrapper expects a pointer to an integer. We pass a buffer.
  result = GuiSpinnerWrapper rect, ^"#{@props.text}\0", valueBuf, @props.minValue, @props.maxValue, @props.editMode
  
  newValue = valueBuf.readInt32LE(0)
  if newValue != @props.value
    @props.value = newValue
    if @props.onChange
      @props.onChange newValue

  FreePTRVal rect

export { Spinner }