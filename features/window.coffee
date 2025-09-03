package gui::window;

import Registry from "./components/registry.coffee";
import { listener } from "./events.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

width = 800;
height = 600;


Object.defineProperty(gui::window::, 'width', {
  get: -> width,
  set: (w) ->
    width = w;
    SetWindowSize(width, height)
});

Object.defineProperty(gui::window::, 'height', {
  get: -> height,
  set: (h) ->
    height = h;
    SetWindowSize(width, height)
});

listener.on 'resize', (w, h) ->
  width = w;
  height = h;

function gui::window::init(title, flags, w = 800, h = 600) {
  SetConfigFlags(flags) if flags

  width = w;
  height = h;

  InitWindow w, h, ^"#{title}\0"

  return true;
}

function gui::window::background(color){
  listener._color = color;
}

function gui::window::add(...components){
  components.forEach (component) =>
    Registry[component._type].push(component);
    component.parent = { _children: Registry[component._type] }
}

function gui::window::close(){
  CloseWindow()
}