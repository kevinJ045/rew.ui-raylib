package gui;

# STD Libraries
import "./_std.coffee";

# Main Libraries
import "./features/consts.coffee";
import "./features/utils.coffee";
import raylib from "./features/ffi/def.coffee";
gui::raylib = raylib;

import "./features/loop.coffee";
import "./features/window.coffee";

using namespace rew::ns

gui::events::setOnStart ->

  rew::channel::timeout 1000, ->
    gui::loop::stop()

gui::loop::run()