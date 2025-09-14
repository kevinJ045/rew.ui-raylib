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
};

@{Component('2d'), defaults}
function ScrollPanel(
  @props
)
  # FIXME: This will leak memory every time a ScrollPanel is created.
  # The component architecture needs a way to clean up resources when a component is unmounted.
  @scroll = CreateVector2 0, 0

function ScrollPanel::draw(time)
  rect = CreateRectangle @props.x, @props.y, @props.w, @props.h
  content = CreateRectangle 0, 0, @props.content_w, @props.content_h
  view = CreateRectangle 0, 0, 0, 0
  
  GuiScrollPanelWrapper rect, ^"#{@props.text}\0", content, @scroll, view

  @emit 'scroll', {
    scroll: rew::ptr::readStruct(scroll, { x: 'f32', y: 'f32' }),
    view: rew::ptr::readStruct(scroll, { x: 'f32', y: 'f32', w: 'f32', h: 'f32' })
  }
  
  FreePTRVal rect
  FreePTRVal content
  FreePTRVal view

export { ScrollPanel }