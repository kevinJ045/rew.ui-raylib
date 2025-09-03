import { listener } from "./events.coffee";
import Registry from "./components/registry.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

listener.on 'loop', (time) ->
  
  BeginDrawing()
  
  ClearBackground if listener._color is null or listener._color is undefined then 0xFFFFFFFF else listener._color 
  
  Registry['2d'].forEach (item) ->
    item.draw(time)


  # BeginMode3DWrapper cam


  # # rect = GuiCreateRectangle 300, 200, 100, 30

  # # print ptr::readStruct rect, { x: 'u32' }
  # # rlPushMatrix()
  # # rlTranslatef(0, 0, 0)
  # # rlRotatef(r1, 1, 0, 0)
  # # rlRotatef(r2, 0, 1, 0)
  # # rlRotatef(r3, 0, 0, 1)
  # # DrawCubeVWrapper pos, sv, RAYCOL

  # rot = CreateVector3 0, 1, 0
  # UpdateModelAnimationWrapper2 model, animations, 7, frame
  # DrawModelExWrapper model, pos, rot, r2, sv, 0xFFFFFFFF
  # # rlPopMatrix()

  # r2 += 0.1

  # frame += 1

  # EndMode3D()
  EndDrawing()