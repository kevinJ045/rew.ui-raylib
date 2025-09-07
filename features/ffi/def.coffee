
import raylib_funcs_auto from "./_values.coffee";
using namespace rew::ns;

raylib_funcs = instantiate class extends raylib_funcs_auto
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateMatrix = -> ffi::ptr
  ffi_type() CreateMatrixWrapper = -> ffi::ptr

  ffi_type(ffi::f32, ffi::f32) CreateVector2 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32) CreateVector3 = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::f32, ffi::f32, ffi::f32) SetVector3Vals = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateRectangle = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3D = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3DOrtho = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::ptr, ffi::f32, ffi::u8) CreateCamera3DDefault = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::ptr, ffi::f32) SetCamera3DVal = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) SetCamera3DPos = -> ffi::void

  ffi_type(ffi::ptr) FreePTRVal = -> ffi::void

  ffi_type() GetMatrixModelviewWrapper = -> ffi::ptr
  ffi_type() GetMatrixProjectionWrapper = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr) MatrixMultiplyW = -> ffi::ptr

  ffi_type(ffi::ptr, ffi::ptr) SetLightPBRPos = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) UpdateLightPBR = -> ffi::void
  ffi_type(ffi::u32, ffi::u32, ffi::ptr, ffi::ptr, ffi::u64, ffi::f32, ffi::ptr) CreateLightPBR = -> ffi::ptr

  ffi_type(ffi::ptr, ffi::f32) Vector3ScaleW = -> ffi::ptr
  ffi_type(ffi::ptr) Vector3NormalizeW = -> ffi::ptr
  ffi_type(ffi::u64) ColorNormalizeW = -> ffi::ptr

  ffi_type(ffi::ptr, ffi::i32) UpdateCamera = -> rew::ffi::void
  ffi_type(ffi::ptr, ffi::i32, ffi::ptr, ffi::i32) SetShaderValueWrapper = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) GetLightViewProj = -> ffi::void
  ffi_type(ffi::ptr, ffi::u32, ffi::buffer) SetShaderLoc = -> ffi::void

  ffi_type(ffi::ptr, ffi::ptr) LoadModelAnimations = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr) SetMaterialShader = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr, ffi::i32, ffi::i32) UpdateModelAnimationWrapper2 = -> ffi::ptr
  ffi_type(ffi::ptr) GetCameraPosition = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::u32) DoStuffPls = -> ffi::ptr

  ffi_type(ffi::ptr, ffi::u32, ffi::buffer, ffi::ptr) SetMaterialMapValue = -> ffi::ptr

  ffi_type() rlPushMatrix = -> ffi::void
  ffi_type() rlPopMatrix = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlTranslatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) rlRotatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlScalef = -> ffi::void

  ffi_type(ffi::ptr, ffi::u64, ffi::u64, ffi::u64, ffi::u64, ffi::u64) SetMaterialColors = -> ffi::void
  ffi_type(ffi::u32, ffi::u32) LoadShadowmapRenderTexture = -> ffi::ptr
  

raylib = rew::ffi::open './.artifacts/librayshim.so', raylib_funcs

module.exports = raylib