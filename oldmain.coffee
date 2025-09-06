import "#std.ffi!";
import "#std.encoding!";
import "#std.types!";
import "#std.os!";
using namespace rew::ns;
using namespace Math;

import raylib_funcs_auto from "./features/ffi/_values.coffee";

raylib_funcs = instantiate class extends raylib_funcs_auto
  ffi_type(ffi::f32, ffi::f32, ffi::f32) CreateVector3 = -> ffi::ptr
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) CreateRectangle = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::f32) CreateCamera3D = -> ffi::ptr

  ffi_type(ffi::ptr, ffi::ptr) LoadModelAnimations = -> ffi::ptr
  ffi_type(ffi::ptr, ffi::ptr, ffi::i32, ffi::i32) UpdateModelAnimationWrapper2 = -> ffi::ptr

  ffi_type() rlPushMatrix = -> ffi::void
  ffi_type() rlPopMatrix = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlTranslatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32, ffi::f32) rlRotatef = -> ffi::void
  ffi_type(ffi::f32, ffi::f32, ffi::f32) rlScalef = -> ffi::void

raylib = rew::ffi::open './.artifacts/librayshim.so', raylib_funcs

using namespace raylib;

RAYWHITE = 0xFF000000
RAYCOL = 0xFF00FF00
RAYCOL2 = 0xFFFF0000

SetConfigFlags 0x00000004
InitWindow 800, 600, ^"hi\0"

pos = CreateVector3 0, -1, 0
campos = CreateVector3 5, 1, 5
target = CreateVector3 0, 0, 0
sv = CreateVector3 1, 1, 1
up = CreateVector3 0, 1, 0
cam = CreateCamera3D campos, target, 45.0

glb = ^"/home/makano/workspace/svre3d/packages/i/bin/objects/cubixc7.glb\0"
model = LoadModelWrapper glb
animations = LoadModelAnimations(&glb, &8);

r1 = 0
r2 = 0
r3 = 0
frame = 0

SetTargetFPS 120

loop {
  if WindowShouldClose()
    break

  BeginDrawing()
  ClearBackground 0xFFFFFFFF
  DrawRectangle 10, 30, 100, 30, RAYCOL2
  DrawText ^"hiii\0", 30, 30, 30, RAYCOL
  rect = CreateRectangle 10, 300, 100, 20
  GuiButtonWrapper rect, ^"hiii\0"
  BeginMode3DWrapper cam


  # rect = GuiCreateRectangle 300, 200, 100, 30

  # print ptr::readStruct rect, { x: 'u32' }
  # rlPushMatrix()
  # rlTranslatef(0, 0, 0)
  # rlRotatef(r1, 1, 0, 0)
  # rlRotatef(r2, 0, 1, 0)
  # rlRotatef(r3, 0, 0, 1)
  # DrawCubeVWrapper pos, sv, RAYCOL

  rot = CreateVector3 0, 1, 0
  UpdateModelAnimationWrapper2 model, animations, 7, frame
  DrawModelExWrapper model, pos, rot, r2, sv, 0xFFFFFFFF
  # rlPopMatrix()

  r2 += 0.1

  frame += 1

  EndMode3D()
  EndDrawing()
}

CloseWindow()