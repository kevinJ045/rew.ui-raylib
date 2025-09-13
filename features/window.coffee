package gui::window;

import Registry from "./components/registry.coffee";
import { listener } from "./events.coffee";

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

width = 800;
height = 600;

camera = null;
campos = null;
camtarget = null;

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

Object.defineProperty(gui::window::, 'camera', {
  get: -> camera,
});

Object.defineProperty(gui::window::, 'campos', {
  get: -> rew::ptr::readStruct campos, { 'x': 'f32', 'y': 'f32', 'z': 'f32' }
});

listener.on 'resize', (w, h) ->
  width = w;
  height = h;

function gui::window::init(title, flags, w = 800, h = 600) {
  SetConfigFlags(flags) if flags

  width = w;
  height = h;

  InitWindow w, h, ^"#{title}\0"

  R3D_Init w, h, 0

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

function gui::window::createCamera(){

  # campos = CreateVector3 0, 5, 0
  # camtarget = CreateVector3 0, 0, 0
  # up = CreateVector3 0.0, 1.0, 0.0
  # camera = CreateCamera3DDefault campos, camtarget, up, 45.0, gui::consts::CAMERA_PERSPECTIVE
  campos = CreateVector3 5, 1, 5
  camtarget = CreateVector3 0, 0, 0
  camera = CreateCamera3D campos, camtarget, 45.0
}

function gui::window::setCameraPosition(x, y, z){
  FreePTRVal campos
  campos = CreateVector3 x, y, z
  SetCamera3DVal camera, campos, camtarget, 45.0
}

function gui::window::close(){
  CloseWindow()
}