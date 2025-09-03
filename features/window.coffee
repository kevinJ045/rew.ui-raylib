package gui::window;

import Registry from "./components/registry.coffee";
import { listener } from "./events.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;


function gui::window::init(title, flags, w = 800, h = 600) {
  SetConfigFlags(flags) if flags

  InitWindow w, h, ^"#{title}\0"

  return true;
}

function gui::window::background(color){
  listener._color = color;
}

function gui::window::add(...components){
  components.forEach (component) =>
    Registry[component._type].push(component);
}

function gui::window::close(){
  CloseWindow()
}