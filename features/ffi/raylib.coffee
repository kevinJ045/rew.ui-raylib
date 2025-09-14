using compiler::coffeeClasses.enable;

using namespace rew::ns

class Texture2D
  constructor: (@ptr) ->

  draw: (x, y, tint) ->
    DrawTextureWrapper @ptr, x, y, tint

  drawV: (position, tint) ->
    DrawTextureVWrapper @ptr, position, tint
  
  drawEx: (position, rotation, scale, tint) ->
    DrawTextureExWrapper @ptr, position, rotation, scale, tint

  unload: ->
    UnloadTextureWrapper @ptr

class Image
  constructor: (@ptr) ->

  unload: ->
    UnloadImageWrapper @ptr

class Model
  constructor: (@ptr) ->

  unload: ->
    UnloadModelWrapper @ptr

LoadTexture = (path) ->
  ptr = LoadTextureWrapper(path)
  if ptr
    return new Texture2D(ptr)
  else
    return null

LoadImage = (path) ->
  ptr = LoadImageWrapper(path)
  if ptr
    return new Image(ptr)
  else
    return null

LoadTextureFromImage = (image) ->
  ptr = LoadTextureFromImageWrapper(image.ptr)
  if ptr
    return new Texture2D(ptr)
  else
    return null

LoadModel = (path) ->
  ptr = LoadModelWrapper(path)
  if ptr
    return new Model(ptr)
  else
    return null

class Vector2
  constructor: (@ptr) ->
  get_x: -> rew::ptr.read(@ptr, 'f32', 0)
  get_y: -> rew::ptr.read(@ptr, 'f32', 4)
  set_x: (x) -> rew::ptr.write(@ptr, x, 'f32', 0)
  set_y: (y) -> rew::ptr.write(@ptr, y, 'f32', 4)

class Vector3
  constructor: (@ptr) ->
  get_x: -> rew::ptr.read(@ptr, 'f32', 0)
  get_y: -> rew::ptr.read(@ptr, 'f32', 4)
  get_z: -> rew::ptr.read(@ptr, 'f32', 8)
  set_x: (x) -> rew::ptr.write(@ptr, x, 'f32', 0)
  set_y: (y) -> rew::ptr.write(@ptr, y, 'f32', 4)
  set_z: (z) -> rew::ptr.write(@ptr, z, 'f32', 8)

class Vector4
  constructor: (@ptr) ->
  get_x: -> rew::ptr.read(@ptr, 'f32', 0)
  get_y: -> rew::ptr.read(@ptr, 'f32', 4)
  get_z: -> rew::ptr.read(@ptr, 'f32', 8)
  get_w: -> rew::ptr.read(@ptr, 'f32', 12)
  set_x: (x) -> rew::ptr.write(@ptr, x, 'f32', 0)
  set_y: (y) -> rew::ptr.write(@ptr, y, 'f32', 4)
  set_z: (z) -> rew::ptr.write(@ptr, z, 'f32', 8)
  set_w: (w) -> rew::ptr.write(@ptr, w, 'f32', 12)

class Color
  constructor: (@ptr) ->
  get_r: -> rew::ptr.read(@ptr, 'u8', 0)
  get_g: -> rew::ptr.read(@ptr, 'u8', 1)
  get_b: -> rew::ptr.read(@ptr, 'u8', 2)
  get_a: -> rew::ptr.read(@ptr, 'u8', 3)
  set_r: (r) -> rew::ptr.write(@ptr, r, 'u8', 0)
  set_g: (g) -> rew::ptr.write(@ptr, g, 'u8', 1)
  set_b: (b) -> rew::ptr.write(@ptr, b, 'u8', 2)
  set_a: (a) -> rew::ptr.write(@ptr, a, 'u8', 3)

class Rectangle
  constructor: (@ptr) ->
  get_x: -> rew::ptr.read(@ptr, 'f32', 0)
  get_y: -> rew::ptr.read(@ptr, 'f32', 4)
  get_width: -> rew::ptr.read(@ptr, 'f32', 8)
  get_height: -> rew::ptr.read(@ptr, 'f32', 12)
  set_x: (x) -> rew::ptr.write(@ptr, x, 'f32', 0)
  set_y: (y) -> rew::ptr.write(@ptr, y, 'f32', 4)
  set_width: (w) -> rew::ptr.write(@ptr, w, 'f32', 8)
  set_height: (h) -> rew::ptr.write(@ptr, h, 'f32', 12)

class Camera2D
  constructor: (@ptr) ->

class Camera3D
  constructor: (@ptr) ->

_CreateVector2 = gui::raylib.CreateVector2
_CreateVector3 = gui::raylib.CreateVector3
_CreateVector4 = gui::raylib.CreateVector4
_CreateRectangle = gui::raylib.CreateRectangle
_CreateCamera2D = gui::raylib.CreateCamera2D
_CreateCamera3D = gui::raylib.CreateCamera3D

CreateVector2 = (x, y) -> new Vector2(_CreateVector2(x, y))
CreateVector3 = (x, y, z) -> new Vector3(_CreateVector3(x, y, z))
CreateVector4 = (x, y, z, w) -> new Vector4(_CreateVector4(x, y, z, w))
CreateRectangle = (x, y, width, height) -> new Rectangle(_CreateRectangle(x, y, width, height))
CreateCamera2D = (offset, target, rotation, zoom) -> new Camera2D(_CreateCamera2D(offset.ptr, target.ptr, rotation, zoom))
CreateCamera3D = (position, target, fovy) -> new Camera3D(_CreateCamera3D(position.ptr, target.ptr, fovy))

export {
  Texture2D, LoadTexture, Image, LoadImage, LoadTextureFromImage, Model, LoadModel,
  Vector2, Vector3, Vector4, Color, Rectangle, Camera2D, Camera3D,
  CreateVector2, CreateVector3, CreateVector4, CreateRectangle,
  CreateCamera2D, CreateCamera3D
}