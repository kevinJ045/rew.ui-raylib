import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

@{Component('3d')}
function Cube(
  @w,
  @h,
  @d,
  @color = 0xFFFFFFFF,
  @model_path
)
  @pos = { x: 0, y: 0, z: 0 }
  @rot = { x: 0, y: 0, z: 0 }
  @scale = { x: 1, y: 1, z: 1 }
  @model = if @model_path then LoadModelWrapper ^"#{@model_path}\0" else LoadModelFromMeshWrapper GenMeshCubeWrapper @w, @h, @d
  # SetMaterialColors @model, @color, 0xff000000, 0xffffff00, 0xff000000, 0xffffff00

  if gui::shadow::_shader
    SetMaterialShader @model, gui::shadow::_shader

function Cube::mat(options)
  @material = gui::material::new options
  @material.apply(@model)

function Cube::draw(time, shadow_instance)

  unless shadow_instance
    @material?.update(time)

  pos = CreateVector3 @pos.x, @pos.y, @rot.z
  rot = CreateVector3 @rot.x, @rot.y, @pos.z
  scale = CreateVector3 @scale.x, @scale.y, @scale.z
  DrawModelExWrapper @model, pos, rot, 0.0, scale, 0xFFFFFFFF
  FreePTRVal scale
  FreePTRVal pos
  FreePTRVal rot

export { Cube }