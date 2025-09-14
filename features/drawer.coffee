import { listener } from "./events.coffee";
import Registry from "./components/registry.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

listener.on 'loop', (time) ->

  color = if listener._color is null or listener._color is undefined then 0xFFFFFFFF else listener._color 

  BeginDrawing()
      
  ClearBackground color

  Registry['2d']
    .filter((item) -> !item.hidden)
    .filter((item) -> item.layer == -1)
    .forEach (item) ->
      item._draw(time)
      item.emitter.emit('draw', time)

  if gui::window::camera
    UpdateCamera(gui::window::camera, gui::consts::CAMERA_ORBITAL) if gui::window::camera_orbital
    R3D_BeginWrapper gui::window::camera
    
    Registry['3d'].filter((item) -> !item.hidden).forEach (item) ->
      item._draw(time)
      item.emitter.emit('draw', time)

    R3D_EndWrapper()

  Registry['2d']
    .filter((item) -> !item.hidden)
    .filter((item) -> item.layer > -1)
    .sort((a, b) => b.layer - a.layer).forEach (item) ->
      item._draw(time)
      item.emitter.emit('draw', time)

  EndDrawing()