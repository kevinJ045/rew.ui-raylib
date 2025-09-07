package gui::shadow;

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

shadow::active = false
shadow::_texture = null
shadow::camera = null

viewPos = null
lightDir = null
lightDirLoc = null
lightVPLoc = null
shadowMapLoc = null

shadow::init = (size = 1024) ->
  shadow::_shader = LoadShaderWrapper ^'assets/shadow.vs\0', ^'assets/shadow.fs\0'
  shadowShader = shadow::_shader
  
  # Look at this if it fails
  b = ^"viewPos\0"
  SetShaderLocVectorView(shadow::_shader, b);
  viewPos = GetShaderLocationWrapper(shadowShader, b)

  lightDir = Vector3NormalizeW CreateVector3 0.35, -1.0, -0.35
  lightColor = 0xFFFFFFFF


  lightDirLoc = GetShaderLocationWrapper(shadowShader, ^"lightDir\0");
  lightColLoc = GetShaderLocationWrapper(shadowShader, ^"lightColor\0");
  
  SetShaderValueWrapper(shadowShader, lightDirLoc, lightDir, SHADER_UNIFORM_VEC3);
  SetShaderValueWrapper(shadowShader, lightColLoc, ColorNormalizeW(lightColor), SHADER_UNIFORM_VEC4);

  ambientLoc = GetShaderLocationWrapper(shadowShader, ^"ambient\0");
  ambient = new Float32Array([
    0.5, 0.5, 0.5, 0.1
  ])
  SetShaderValueWrapper(shadowShader, ambientLoc, &ambient, SHADER_UNIFORM_VEC4);


  lightVPLoc = GetShaderLocationWrapper(shadowShader, ^"lightVP\0");
  shadowMapLoc = GetShaderLocationWrapper(shadowShader, ^"shadowMap\0");

  SetShaderValueWrapper(shadowShader, GetShaderLocationWrapper(shadowShader, ^"shadowMapResolution\0"), &size, SHADER_UNIFORM_INT);

  shadow::_texture = LoadShadowmapRenderTexture size, size

  campos = Vector3ScaleW(lightDir, -15.0);
  camtarget = CreateVector3 0, 0, 0
  camera = CreateCamera3DOrtho campos, camtarget, 20.0

  shadow::camera = camera
  shadow::active = true

shadow::update = (lightView, lightProj) ->
  lightDir = Vector3NormalizeW(lightDir);
  position = Vector3ScaleW(lightDir, -15.0);
  SetCamera3DPos shadow::camera, position
  SetShaderValueWrapper(shadow::_shader, lightDirLoc, lightDir, SHADER_UNIFORM_VEC3);

  camp = GetCameraPosition(gui::window::camera)
  SetShaderValueWrapper(shadow::_shader, viewPos, camp, SHADER_UNIFORM_VEC3);

  lightViewProj = MatrixMultiplyW(lightView, lightProj)

  SetShaderValueMatrixWrapper(shadow::_shader, lightVPLoc, lightViewProj);

  DoStuffPls shadow::_shader, shadow::_texture, shadowMapLoc
