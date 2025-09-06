package gui::shadow;

using namespace gui::raylib;

shadow::active = false
shadow::_texture = null
shadow::camera = null

shadow::init = (x = 1024, y = 1024) ->
  shadow::_shader = LoadShaderWrapper ^'assets/shadow.vs\0', ^'assets/shadow.fs\0'
  shadow::_texture = LoadRenderTextureWrapper x, y
  campos = CreateVector3 0, 5, 0
  camtarget = CreateVector3 0, 0, 0
  up = CreateVector3 0, 1, 0
  camera = CreateCamera3DDefault campos, camtarget, up, 45.0, gui::consts::CAMERA_ORTHOGRAPHIC
  shadow::locLightVP = GetShaderLocationWrapper(shadow::_shader, ^"lightViewProj\0")
  shadow::locShadowMap = GetShaderLocationWrapper(shadow::_shader, ^"shadowMap\0")
  shadow::camera = camera
  shadow::active = true

shadow::update = () ->
  lightMatrix = CreateMatrixWrapper()
  GetLightViewProj shadow::camera, lightMatrix

  SetShaderValueTextureWrapper shadow::_shader, shadow::locShadowMap, shadow::_texture
  SetShaderValueMatrixWrapper(shadow::_shader, shadow::locLightVP, lightMatrix)

  FreePTRVal(lightMatrix)