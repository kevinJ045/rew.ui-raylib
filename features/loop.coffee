package gui::loop;

import { mainEvents } from "./events.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

running = false

Object.defineProperty(gui::loop::, 'running', {
  get: -> running
});


function gui::loop::run(fps = 0, time = 1) {
  running = true;

  SetTargetFPS(fps) if fps

  mainEvents._onStart()

  start = ->
    if IsWindowResized()
      mainEvents._resize(GetRenderWidth(), GetRenderHeight())

    if WindowShouldClose()
      CloseWindow()
      running = mainEvents._beforeQuit();
  
  frame = ->
    mainEvents._loop(GetFrameTime())

  if fps
    loop {
      start()

      unless running
        mainEvents._onQuit()
        break
      
      frame()
    }
  else
    rew::channel::new time, ->
      start()

      unless running
        mainEvents._onQuit()
        return @stop()

      frame()


}

function gui::loop::stop() {
  running = false;
}
