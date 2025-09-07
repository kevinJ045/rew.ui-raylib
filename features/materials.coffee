package gui::material;

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

shader = null
viewPos = null
metallicValueLoc = null
roughnessValueLoc = null
emissiveIntensityLoc = null
emissiveColorLoc = null
textureTilingLoc = null

lightCount = 0
MAX_LIGHTS = 4
lights = []

function init()
  shader = LoadShaderWrapper ^'assets/pbr.vs\0', ^'assets/pbr.fs\0'

  SetShaderLoc shader, SHADER_LOC_MAP_ALBEDO, ^"albedoMap\0"
  SetShaderLoc shader, SHADER_LOC_MAP_METALNESS, ^"mraMap\0"
  SetShaderLoc shader, SHADER_LOC_MAP_NORMAL, ^"normalMap\0"
  SetShaderLoc shader, SHADER_LOC_MAP_EMISSION, ^"emissiveMap\0"
  SetShaderLoc shader, SHADER_LOC_COLOR_DIFFUSE, ^"albedoColor\0"

  SetShaderLoc shader, SHADER_LOC_VECTOR_VIEW, ^"viewPos\0"

  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"ambientColor\0"), &(new Float32Array(gui::shadow::getAmbient())), SHADER_UNIFORM_VEC3);
  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"ambient\0"), &(gui::shadow::getAmbientIntensity()), SHADER_UNIFORM_FLOAT);

  metallicValueLoc = GetShaderLocationWrapper(shader, ^"metallicValue\0");
  roughnessValueLoc = GetShaderLocationWrapper(shader, ^"roughnessValue\0");
  emissiveIntensityLoc = GetShaderLocationWrapper(shader, ^"emissivePower\0");
  emissiveColorLoc = GetShaderLocationWrapper(shader, ^"emissiveColor\0");
  textureTilingLoc = GetShaderLocationWrapper(shader, ^"tiling\0");
  
  viewPos = GetShaderLocationWrapper(shader, ^"viewPos\0");

  # tell shader max lights
  numLightsLoc = GetShaderLocationWrapper(shader, ^"numOfLights\0")
  SetShaderValueWrapper(shader, numLightsLoc, &(new Int32Array([MAX_LIGHTS])), SHADER_UNIFORM_INT)

  usage = new Int32Array [1];
  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"useTexAlbedo\0"), &usage, SHADER_UNIFORM_INT);
  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"useTexNormal\0"), &usage, SHADER_UNIFORM_INT);
  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"useTexMRA\0"), &usage, SHADER_UNIFORM_INT);
  SetShaderValueWrapper(shader, GetShaderLocationWrapper(shader, ^"useTexEmissive\0"), &usage, SHADER_UNIFORM_INT);


DefaultOptions = const_rec {
  albedo: WHITE,
  metallic: 0.0,
  roughness: 1.0,
  occlusion: 0.0,
  emission: BLACK,
  normal: WHITE,

  emissiveIntensity: 0.0,

  albedoMap: null,
  metalMap: null,
  normalMap: null,
  emissionMap: null,
  textureTiling: null
}

function Material(options = DefaultOptions)
  @options = { ...DefaultOptions, ...options }
  print @options
  unless shader
    init()
  @shader = shader;

function Material::apply(model)
  SetMaterialShader model, shader

  color = ^'color\0'
  value = ^'value\0'
  texture = ^'texture\0'

  SetMaterialMapValue model, MATERIAL_MAP_ALBEDO, color, &(new Int32Array([@options.albedo]))
  SetMaterialMapValue model, MATERIAL_MAP_METALNESS, value, &(@options.metallic)
  SetMaterialMapValue model, MATERIAL_MAP_ROUGHNESS, value, &(@options.roughness)
  SetMaterialMapValue model, MATERIAL_MAP_OCCLUSION, value, &(@options.occlusion)
  SetMaterialMapValue model, MATERIAL_MAP_EMISSION, color, &(new Int32Array([@options.emission]))

  SetMaterialMapValue model, MATERIAL_MAP_ALBEDO, texture, @options.albedoMap if @options.albedoMap
  SetMaterialMapValue model, MATERIAL_MAP_METALNESS, texture, @options.metalMap if @options.metalMap
  SetMaterialMapValue model, MATERIAL_MAP_NORMAL, texture, @options.normalMap if @options.normalMap
  SetMaterialMapValue model, MATERIAL_MAP_EMISSION, texture, @options.emissionMap if @options.emissionMap

function Material::update(time)
  { emission, emissiveIntensity, metallic, roughness } = @options

  SetShaderValueWrapper shader, textureTilingLoc, @options.textureTiling, SHADER_UNIFORM_VEC2 if @options.textureTiling

  SetShaderValueWrapper shader, emissiveColorLoc, ColorNormalizeW(emission), SHADER_UNIFORM_VEC4
  SetShaderValueWrapper shader, emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT

  SetShaderValueWrapper shader, metallicValueLoc, &metallic, SHADER_UNIFORM_FLOAT
  SetShaderValueWrapper shader, roughnessValueLoc, &roughness, SHADER_UNIFORM_FLOAT

gui::material::new = (o = DefaultOptions) -> new Material(o)

function gui::material::update()
  unless shader
    init()
  
  cameraPos = GetCameraPosition(gui::window::camera)
  SetShaderValueWrapper(shader, viewPos, cameraPos, SHADER_UNIFORM_VEC3);

  # update all lights in shader
  for l of lights
    UpdateLight(shader, l)

function CreateLight(type, position, target, color, intensity)
  pos = CreateVector3(position.x, position.y, position.z)
  targ = CreateVector3(target.x, target.y, target.z)
  light = CreateLightPBR(MAX_LIGHTS, type, pos, targ, color, intensity, shader)
  lights.push light
  light

gui::material::light = (...args) -> CreateLight ...args  

function UpdateLight(shader, light)
  UpdateLightPBR shader, light
