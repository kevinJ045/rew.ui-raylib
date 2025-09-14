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
  value: 50,
  minValue: 0,
  maxValue: 100
};

@{Component('2d'), defaults}
function Slider(
  @props
)
  # Create a buffer to hold the float value.
  valueBuf = rew::ffi::buffer(4)
  valueBuf.writeFloatLE(@props.value, 0)

function Slider::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  
  # The wrapper expects a pointer to a float. We pass a buffer.
  # This might work if the FFI layer is smart enough to treat a buffer as a pointer.
  result = GuiSliderWrapper rect, ^"#{@props.textLeft}\0", ^"#{@props.textRight}\0", valueBuf, @props.minValue, @props.maxValue
  
  newValue = valueBuf.readFloatLE(0)
  if newValue != @props.value
    @props.value = newValue
    if @props.onChange
      @props.onChange newValue

  FreePTRVal rect

export { Slider }