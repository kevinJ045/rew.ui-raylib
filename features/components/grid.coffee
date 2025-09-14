import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

defaults = {
  slices: 10,
  spacing: 1.0,
  x: 0,
  y: 0,
  z: 0
};

@{Component('3d'), defaults}
function Grid(
  @props
)

function Grid::draw(time, abs_pos)
  rlPushMatrixWrapper()
  rlTranslatefWrapper(abs_pos.x, abs_pos.y, abs_pos.z)
  DrawGrid @props.slices, @props.spacing
  rlPopMatrixWrapper()

export { Grid }