import "#std.ffi!";
import "#std.encoding!";
import "#std.types!";
import "#std.os!";
using namespace rew::ns;

import raylib_funcs_auto from "./features/ffi/_values.coffee";

raylib_funcs = instantiate class extends raylib_funcs_auto
  ffi_type(ffi::f32, ffi::f32, ffi::f32) CreateVector3 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateRectangle = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3D = -> ffi::ptr

raylib = rew::ffi::open './.artifacts/librayshim.so', raylib_funcs

using namespace raylib;

RAYWHITE = 0xFFFFFFFF
RAYCOL = 0xFF00FF00
RAYCOL2 = 0xFF000000

InitWindow 800, 400, toBytes "hi\0"

pos = CreateVector3 0, 0, 0
campos = CreateVector3 5, 2, 5
target = CreateVector3 0, 0, 0
up = CreateVector3 0, 1, 0
cam = CreateCamera3D campos, target, 45.0

loop {
  if WindowShouldClose()
    break

  BeginDrawing()
  ClearBackground RAYWHITE
  DrawRectangle 10, 30, 100, 30, RAYCOL2
  DrawText toBytes("hiii\0"), 30, 30, 30, RAYCOL
  rect = CreateRectangle 10, 300, 100, 20
  GuiButtonWrapper rect, toBytes("hiii\0")
  BeginMode3DWrapper cam


  # rect = GuiCreateRectangle 300, 200, 100, 30

  # print ptr::readStruct rect, { x: 'u32' }

  DrawCubeWrapper pos, 2, 2, 2, RAYCOL
  
  EndMode3D()
  EndDrawing()
}

CloseWindow()