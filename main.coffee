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
import "./features/drawer.coffee";

using namespace rew::ns



# gui::events::setOnStart ->

#   rew::channel::timeout 1000, ->
#     gui::loop::stop()

gui::window::init("Hello!")

rect = gui::components::Rectangle::new(1, 1, 200, 200)
text = gui::components::Text::new("Hello!!", 1, 220)

gui::window::add rect, text

gui::events.on 'loop', (time) ->
  rect.x += 1

gui::loop::run(60)


