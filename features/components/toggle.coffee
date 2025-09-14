import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 100,
  h: 30,
  text: "",
  active: false
};

@{Component('2d'), defaults}
function Toggle(
  @props
)
  activeBuf = rew::ffi::buffer(1)
  activeBuf.writeInt8(@props.active, 0)

function Toggle::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  
  result = GuiToggleWrapper rect, ^"#{@props.text}\0", activeBuf
  
  newActive = activeBuf.readInt8(0)
  if newActive != @props.active
    @props.active = newActive
    if @props.onChange
      @props.onChange newActive

  FreePTRVal rect

export { Toggle }