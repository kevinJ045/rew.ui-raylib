
import raylib_funcs_auto from "./_values.coffee";
using namespace rew::ns;

raylib_funcs = instantiate class extends raylib_funcs_auto
  ffi_type(ffi::f32, ffi::f32) CreateVector2 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32) CreateVector3 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateRectangle = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3D = -> ffi::ptr

  ffi_type(ffi::ptr) FreePTRVal = -> ffi::void

  ffi_type(ffi::ptr, ffi::ptr) LoadModelAnimations = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::i32, ffi::i32) UpdateModelAnimationWrapper2 = -> ffi::ptr

  ffi_type() rlPushMatrix = -> ffi::void
  ffi_type() rlPopMatrix = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlTranslatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) rlRotatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlScalef = -> ffi::void

raylib = rew::ffi::open './.artifacts/librayshim.so', raylib_funcs

module.exports = raylib