import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 200,
  h: 200,
  text: "",
  padding: 0,
  layout: { type: 'stack', direction: 'vertical', spacing: 5 }
};

@{Component('2d'), defaults}
function Panel(
  @props
)

function Panel::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  GuiPanelWrapper rect, ^"#{@props.text}\0"
  FreePTRVal rect
  
  layout = @props.layout
  
  content_x = abs_pos.x + @props.padding
  content_y = abs_pos.y + @props.padding
  content_w = @props.w - @props.padding * 2
  content_h = @props.h - @props.padding * 2
  
  current_x = 0
  current_y = 0
  
  for child in @_children
    child_props = child.props
    
    if layout.type == 'stack'
      if layout.direction == 'vertical'
        child_props.x = 0
        child_props.y = current_y
        child_props.w ?= content_w
        
        child._draw(time, @)
        
        current_y += child_props.h + layout.spacing
      else # horizontal
        child_props.x = current_x
        child_props.y = 0
        child_props.h ?= content_h
        
        child._draw(time, @)
        
        current_x += child_props.w + layout.spacing
    else # no layout
      child._draw(time, @)

export { Panel }