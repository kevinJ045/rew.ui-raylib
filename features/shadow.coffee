package gui::shadow;

using namespace gui::raylib;

shadow::active = false
shadow::_texture = null
shadow::camera = null

shadow::init = (x = 1024, y = 1024) ->
  shadow::_shader = LoadShaderWrapper ^'assets/shadow.vs', ^'assets/shadow.fs'
  shadow::_texture = LoadRenderTextureWrapper x, y
  campos = CreateVector3 0, 5, 0
  camtarget = CreateVector3 0, 0, 0
  camera = CreateCamera3D campos, camtarget, 45.0
  shadow::camera = camera
  shadow::active = true