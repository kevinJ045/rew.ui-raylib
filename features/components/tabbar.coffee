import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 300,
  h: 30,
  tabs: [],
  active: 0
};

@{Component('2d'), defaults}
function TabBar(
  @props
)
  @activeBuf = rew::ffi::buffer(4)
  @activeBuf.writeInt32LE(@props.active, 0)

function TabBar::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  
  # NOTE: GuiTabBar expects a `const char**` which is an array of strings.
  # The current FFI setup for this function is likely incorrect.
  # We are joining the tabs with a semicolon, like for `DropdownBox`,
  # but this might not work as expected.
  tabs_text = @props.tabs.join(';')
  
  GuiTabBarWrapper rect, ^"#{tabs_text}\0", @props.tabs.length, @activeBuf
  
  newActive = @activeBuf.readInt32LE(0)
  if newActive != @props.active
    @props.active = newActive
    if @props.onChange
      @props.onChange newActive

  FreePTRVal rect

export { TabBar }