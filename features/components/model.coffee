import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

DEG2RAD = Math.PI / 180.0

function getTex(t)
  if typeof t is "object" then t else LoadTextureWrapper ^"#{t}\0"

defaults = {
  pos: { x: 0, y: 0, z: 0 },
  rot: { x: 0, y: 0, z: 0 },
  scale: { x: 1, y: 1, z: 1 },
}

defaultModels = {
  'cube': (props) ->
    R3D_LoadModelFromMeshWrapper R3D_GenMeshCubeWrapper props.size, props.size, props.size, true
  'box': (props) ->
    R3D_LoadModelFromMeshWrapper R3D_GenMeshCubeWrapper props.width, props.height, props.depth, true
  'sphere': (props) ->
    R3D_LoadModelFromMeshWrapper R3D_GenMeshSphereWrapper props.radius, props.rings, props.slices, true
}

getModel = (m, p) ->
  if defaultModels[m]
    defaultModels[m](p)
  else
    R3D_LoadModelWrapper ^"#{m}\0"

@{Component('3d'), defaults}
function Model(
  @props
)
  @model = @props.model
  @pos = @props.pos
  @rot = @props.rot
  @scale = @props.scale

function Model::mat(options, material_index = 0)
  material = R3D_Model_GetMaterial @model, material_index
  if not material
    print "[WARN]", "Material index #{material_index} is out of bounds."
    return

  if options.albedoColor
    R3D_Material_SetAlbedoColor material, options.albedoColor

  if options.albedoTexture
    texture = getTex(options.albedoTexture)
    R3D_Material_SetAlbedoTexture material, texture

  if options.emissionColor
    R3D_Material_SetEmissionColor material, options.emissionColor
  if options.emissionEnergy != null
    R3D_Material_SetEmissionEnergy material, options.emissionEnergy

  if options.normalTexture
    texture = getTex(options.normalTexture)
    R3D_Material_SetNormalTexture material, texture
  if options.normalScale != null
    R3D_Material_SetNormalScale material, options.normalScale

  if options.ormTexture
    texture = getTex(options.ormTexture)
    R3D_Material_SetORMTexture material, texture
  if options.occlusion != null
    R3D_Material_SetORMOcclusion material, options.occlusion
  if options.roughness != null
    R3D_Material_SetORMRoughness material, options.roughness
  if options.metalness != null
    R3D_Material_SetORMMetalness material, options.metalness

  if options.blendMode != null
    R3D_Material_SetBlendMode material, options.blendMode

  if options.cullMode != null
    R3D_Material_SetCullMode material, options.cullMode
  
  if options.uvOffset
    R3D_Material_SetUVOffset material, options.uvOffset

  if options.uvScale
    R3D_Material_SetUVScale material, options.uvScale

  if options.alphaCutoff != null
    R3D_Material_SetAlphaCutoff material, options.alphaCutoff

function Model::draw(time, abs_pos)
  pos = CreateVector3 abs_pos.x, abs_pos.y, abs_pos.z
  rot = CreateVector3 @rot.x, @rot.y, @rot.z
  scale = CreateVector3 @scale.x, @scale.y, @scale.z

  R3D_DrawModelExWrapper @model, pos, rot, 0.0, scale

  FreePTRVal pos
  FreePTRVal rot
  FreePTRVal scale

function Model::from(model_path, props)
  model = getModel(model_path, props)
  Model::new {...props, model}

function Model::cube(w, h, d, props)
  cubeMesh = R3D_GenMeshCubeWrapper w, h, d, true
  model = R3D_LoadModelFromMeshWrapper cubeMesh
  Model::new {...props, model}

function Model::sphere(radius, rings, slices, props)
  sphereMesh = R3D_GenMeshSphereWrapper radius, rings, slices, true
  model = R3D_LoadModelFromMeshWrapper sphereMesh
  Model::new {...props, model}

export { Model }