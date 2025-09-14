
import raylib_funcs_auto from "./_values.coffee";
using namespace rew::ns;

raylib_funcs = instantiate class extends raylib_funcs_auto
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateMatrix = -> ffi::ptr
  ffi_type() CreateMatrixWrapper = -> ffi::ptr

  ffi_type(ffi::f32, ffi::f32) CreateVector2 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32) CreateVector3 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateVector4 = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::f32, ffi::f32, ffi::f32) SetVector3Vals = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateRectangle = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3D = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3DOrtho = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::ptr, ffi::f32, ffi::u8) CreateCamera3DDefault = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::ptr, ffi::f32) SetCamera3DVal = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) SetCamera3DPos = -> ffi::void

  ffi_type(ffi::ptr, ffi::ptr, ffi::u64, ffi::bool) GuiTextBoxWrapper = -> ffi::i32

  ffi_type(ffi::ptr) FreePTRVal = -> ffi::void
  
  ffi_type(ffi::ptr) GenMeshTangents = -> ffi::void
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

  ffi_type(ffi::i32, ffi::i32, ffi::i32, ffi::i32) TG_Voronoi = -> ffi::ptr
  ffi_type(ffi::i32, ffi::i32, ffi::i32, ffi::i32) TG_Checker = -> ffi::ptr
  ffi_type(ffi::i32, ffi::i32, ffi::bool) TG_Gradient = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::i32) TG_AlbedoFromField = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::ptr) TG_MRAFromFields = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::f32) TG_NormalFromHeight = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::i32) TG_NormalFromHeight = -> ffi::ptr
  ffi_type(ffi::i32, ffi::ptr, ffi::ptr) CreateColorStopsFromArrays = -> ffi::ptr

  ffi_type(ffi::i32, ffi::i32, ffi::i32) R3D_Init = -> ffi::void
  ffi_type() GetMatrixIdentity = -> ffi::ptr

  ffi_type(ffi::f32, ffi::f32, ffi::f32) MatrixTranslateW = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32) MatrixScaleW = -> ffi::ptr
  ffi_type(ffi::ptr) MatrixRotateZYXW = -> ffi::ptr

  ffi_type(ffi::i32, ffi::i32) R3D_UpdateResolution = -> ffi::void
  ffi_type(ffi::ptr, ffi::i32) R3D_Model_GetMaterial = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::i64) R3D_Material_SetAlbedoColor = -> ffi::void

  ffi_type(ffi::ptr, ffi::f32) R3D_Material_SetORMOcclusion = -> ffi::void
  ffi_type(ffi::ptr, ffi::f32) R3D_Material_SetORMRoughness = -> ffi::void
  ffi_type(ffi::ptr, ffi::f32) R3D_Material_SetORMMetalness = -> ffi::void
  
  ffi_type(ffi::ptr, ffi::i32) R3D_Material_SetBlendMode = -> ffi::void
  ffi_type(ffi::ptr, ffi::i32) R3D_Material_SetCullMode = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) R3D_Material_SetUVOffset = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) R3D_Material_SetUVScale = -> ffi::void
  ffi_type(ffi::ptr, ffi::f32) R3D_Material_SetAlphaCutoff = -> ffi::void
  
  ffi_type(ffi::ptr, ffi::ptr) R3D_Material_SetAlbedoTexture = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) R3D_Material_SetNormalTexture = -> ffi::void
  ffi_type(ffi::ptr, ffi::ptr) R3D_Material_SetORMTexture = -> ffi::void

  ffi_type() rlPushMatrixWrapper = -> rew::ffi::buffer
  ffi_type() rlPopMatrixWrapper = -> rew::ffi::buffer
  ffi_type(rew::ffi::f32, rew::ffi::f32, rew::ffi::f32) rlTranslatefWrapper = -> rew::ffi::buffer


raylib = rew::ffi::open './.artifacts/librayshim.so', raylib_funcs
raylib.free = raylib.FreePTRVal

module.exports = raylib