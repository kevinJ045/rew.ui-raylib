package gui;

# STD Libraries
import "./_std.coffee!";

# Main Libraries
import "./features/consts.coffee";
import "./features/utils.coffee";
import raylib from "./features/ffi/def.coffee";
gui::raylib = raylib;

import "./features/loop.coffee";
import "./features/window.coffee";
import "./features/components/init.coffee";
import "./features/shadow.coffee";
import "./features/drawer.coffee";

using namespace rew::ns
using namespace raylib



# gui::events::setOnStart ->

#   rew::channel::timeout 1000, ->
#     gui::loop::stop()

gui::window::init("Hello!")
gui::window::background 0xFF000000

gui::window::createCamera()

gui::shadow::init()

cube = gui::components::Cube::new 1, 1, 1, 0xFF00FF00
cube2 = gui::components::Cube::new 10, 0.1, 10, 0xFF00FF00

gui::window::add cube

rew::channel::timeout 1000, ->
  gui::window::setCameraPosition 10, 0, 0

gui::events.on 'loop', (time) ->
  # cube.rot.x += 0.1

rew::channel::timeout 1, -> gui::loop::run(0, 1000 / 400)
