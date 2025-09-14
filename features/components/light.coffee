import { Component, ComponentOverride } from "./base.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

@{Component('light')}
function Light(
  @type = R3D_LIGHT_DIR,
  @col = 0xFFFFFFFF
)
  @pos = { x: 0, y: 0, z: 0 }
  @dir = { x: 0, y: 0, z: 0 }
  @pow = 1.0
  @active = false
  @shadow = false
  @light = R3D_CreateLightWrapper @type
  @ran = R3D_GetLightRangeWrapper @light
  @spec = R3D_GetLightSpecularWrapper @light

function Light::specular(number)
  @spec = number
  R3D_GetLightSpecularWrapper @light, @spec
  @

function Light::range(number)
  @ran = number
  R3D_SetLightRangeWrapper @light, @ran
  @

function Light::color(hex)
  @col = hex
  R3D_SetLightColorWrapper @light, @col
  @

function Light::power(i)
  @pow = i
  R3D_SetLightEnergyWrapper @light, @pow
  @

function Light::move(x, y, z)
  gui::utils::checkVec3 @, 'pos', x, y, z
  pos = CreateVector3 @pos.x, @pos.y, @pos.z
  R3D_SetLightPositionWrapper @light, pos
  FreePTRVal pos
  @

function Light::direct(x, y, z)
  gui::utils::checkVec3 @, 'dir', x, y, z
  dir = CreateVector3 @dir.x, @dir.y, @dir.z
  R3D_SetLightDirectionWrapper @light, dir
  FreePTRVal dir
  @
  
function Light::lookAt(target)
  unless gui::utils::isVec3(target?.pos)
    return
  pos = CreateVector3 @pos.x, @pos.y, @pos.z
  targ = CreateVector3 target.pos.x, target.pos.y, target.pos.z
  R3D_LightLookAtWrapper @light, pos, target
  FreePTRVal pos
  FreePTRVal targ
  @

function Light::shadowOn(size = 1024)
  @shadow = true
  R3D_EnableShadowWrapper @light, size
  @

function Light::shadowOff()
  @shadow = false
  R3D_DisableShadowWrapper @light, true
  @


function Light::enable()
  @active = true
  R3D_SetLightActiveWrapper @light, @active
  @

function Light::disable()
  @active = false
  R3D_SetLightActiveWrapper @light, @active

@{ComponentOverride}
function Light::add()
  @disable()

@{ComponentOverride}
function Light::remove()
  R3D_DestroyLightWrapper @light

function Light.dir()
  Light::new(R3D_LIGHT_DIR - 1)

function Light.spot()
  Light::new(R3D_LIGHT_SPOT - 1)

function Light.omni()
  Light::new(R3D_LIGHT_OMNI - 1)


export { Light }