import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

@{Component('3d')}
function Cube(
  @w,
  @h,
  @d,
  @color = 0xFFFFFFFF
)
  @pos = { x: 0, y: 0, z: 0 }
  @rot = { x: 0, y: 0, z: 0 }
  @scale = { x: 1, y: 1, z: 1 }
  @model = LoadModelFromMeshWrapper GenMeshCubeWrapper @w, @h, @d
  SetMaterialColors @model, @color, 0xff000000, 0xffffff00, 0xff000000, 0xffffff00

  # if gui::shadow::_shader
  #   SetMaterialShader @model, gui::shadow::_shader

function Cube::draw(time)
  pos = CreateVector3 @pos.x, @pos.y, @pos.z
  rlPushMatrix()
  rlTranslatef(0, 0, 0)
  rlRotatef(@rot.x, 1, 0, 0)
  rlRotatef(@rot.y, 0, 1, 0)
  rlRotatef(@rot.z, 0, 0, 1)
  DrawModelWrapper @model, pos, @scale.x, 0xFFFFFFFF
  rlPopMatrix()
  FreePTRVal pos

export { Cube }