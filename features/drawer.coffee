import { listener } from "./events.coffee";
import Registry from "./components/registry.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

listener.on 'loop', (time) ->

  color = if listener._color is null or listener._color is undefined then 0xFFFFFFFF else listener._color 
  
  BeginDrawing()
      
  ClearBackground color
  
  Registry['2d'].forEach (item) ->
    item.draw(time)
    item.emitter.emit('draw', time)

  
  if gui::shadow::active
    BeginTextureModeWrapper gui::shadow::_texture
    ClearBackground color
    BeginMode3DWrapper gui::shadow::camera
    
    Registry['3d'].forEach (item) ->
      item.draw(time)

    EndMode3D()
    EndTextureMode()

    gui::shadow::update()

  if gui::window::camera
    BeginMode3DWrapper gui::window::camera
    
    Registry['3d'].forEach (item) ->
      item.draw(time)
      item.emitter.emit('draw', time)

    EndMode3D()

  EndDrawing()