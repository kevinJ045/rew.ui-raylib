import { Component } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;

DEG2RAD = Math.PI / 180.0

function getTex(t)
  if typeof t is "object" then t else LoadTextureWrapper ^"#{t}\0"

@{Component('3d')}
function Model(
  @model
)
  @pos = { x: 0, y: 0, z: 0 }
  @rot = { x: 0, y: 0, z: 0 }
  @scale = { x: 1, y: 1, z: 1 }

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

function Model::draw(time, parent)
  pos = gui::utils::vec3ptr @pos
  rot = gui::utils::vec3ptr @rot
  scale = gui::utils::vec3ptr @scale

  R3D_DrawModelExWrapper @model, pos, rot, 0.0, scale

  FreePTRVal pos
  FreePTRVal rot
  FreePTRVal scale

  # trans = MatrixTranslateW @pos.x, @pos.y, @pos.z
  # rotMat = MatrixRotateZYXW CreateVector3(@rot.x * DEG2RAD, @rot.y * DEG2RAD, @rot.z * DEG2RAD)
  # scaleMat = MatrixScaleW @scale.x, @scale.y, @scale.z

  # transform = MatrixMultiplyW scaleMat, rotMat
  # transform = MatrixMultiplyW transform, trans

  # R3D_DrawModelProWrapper @model, transform

function Model::from(model_path)
  model = R3D_LoadModelWrapper ^"#{model_path}\0"
  Model::new model

function Model::cube(w, h, d)
  cubeMesh = R3D_GenMeshCubeWrapper w, h, d, true
  model = R3D_LoadModelFromMeshWrapper cubeMesh
  Model::new model

function Model::sphere(radius, rings, slices)
  sphereMesh = R3D_GenMeshSphereWrapper radius, rings, slices, true
  model = R3D_LoadModelFromMeshWrapper sphereMesh
  Model::new model

export { Model }