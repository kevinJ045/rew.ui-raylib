import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 200,
  text: "",
  content_w: 400,
  content_h: 400,
  padding: 0
};

@{Component('2d'), defaults}
function ScrollPanel(
  @props
)
  @scroll = CreateVector2 0, 0

function ScrollPanel::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  content = CreateRectangle 0, 0, @props.content_w, @props.content_h
  view = CreateRectangle 0, 0, 0, 0
  
  GuiScrollPanelWrapper rect, ^"#{@props.text}\0", content, @scroll, view

  BeginScissorMode view.x, view.y, view.w, view.h
  
  dummy_parent = {
    abs_pos: {
      x: abs_pos.x + @props.padding - @scroll.x,
      y: abs_pos.y + @props.padding - @scroll.y,
      z: 0
    },
    props: {
      padding: 0
    }
  }
  
  for child in @_children
    child._draw(time, dummy_parent)
    
  EndScissorMode()

  FreePTRVal rect
  FreePTRVal content
  FreePTRVal view

export { ScrollPanel }