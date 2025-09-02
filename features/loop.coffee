package gui::loop;

import { mainEvents } from "./events.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

running = false

Object.defineProperty(gui::loop::, 'running', {
  get: -> running
});


function gui::loop::run(fps = 0) {
  running = true;

  SetTargetFPS(fps) if fps

  mainEvents._onStart()

  loop {
    if WindowShouldClose()
      running = mainEvents._beforeQuit() ?? false;

    unless running
      mainEvents._onQuit()
      break

    mainEvents._loop()
  }
}

function gui::loop::stop() {
  running = false;
}
