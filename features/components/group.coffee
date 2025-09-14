import { Component } from "./base.coffee";

@{Component('3d')}
function Group(
  @props
)

function Group::draw(time, abs_pos)
  # This component only groups children, it does not draw anything by itself.
  # The layout is handled by the `_draw` method in `base.coffee`.
  pass

export { Group }