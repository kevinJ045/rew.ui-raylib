import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  x: 0,
  y: 0,
  w: 150,
  h: 100,
  items: [],
  scrollIndex: 0,
  active: 0
};

@{Component('2d'), defaults}
function ListView(
  @props
)
  @scrollIndex = &(@props.scrollIndex)
  @active = &(@props.active)

function ListView::draw(time, abs_pos)
  rect = CreateRectangle abs_pos.x, abs_pos.y, @props.w, @props.h
  text = @props.items.join(';')
  result = GuiListViewWrapper rect, ^"#{text}\0", @scrollIndex, @active
  active = *@active
  scrollIndex = *@scrollIndex
  if active !== @props.active
    @props.active = active
    @emit 'change', active
  if scrollIndex !== @props.scrollIndex
    @props.scrollIndex = scrollIndex
    @emit 'scroll', scrollIndex
  FreePTRVal rect

export { ListView }