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
import "./features/materials.coffee";
import "./features/drawer.coffee";

using namespace rew::ns
using namespace raylib



# gui::events::setOnStart ->

#   rew::channel::timeout 1000, ->
#     gui::loop::stop()

gui::window::init("Hello!", gui::consts::FLAG_MSAA_4X_HINT)
gui::window::background 0xFF000000

gui::window::createCamera()
gui::window::camera_orbital = true

gui::shadow::init()

cube = gui::components::Cube::new 1, 1, 1, 0xFFDDDDDD, '.artifacts/old_car_new.glb'
cube.scale.x = 0.1
cube.scale.y = 0.1
cube.scale.z = 0.1
cube2 = gui::components::Cube::new 10, 0.1, 10, 0xFFFFFFFF
cube2.pos.y = -0.1

cube.mat {
  albedo: 0xFFFFFFFF,
  roughness: 0.0,
  metallic: 1.0,
  occlusion: 1.0,
  emissive: 0xFF00DDFF,

  albedoMap: LoadTextureWrapper(^".artifacts/old_car_d.png\0"),
  metalMap: LoadTextureWrapper(^".artifacts/old_car_mra.png\0"),
  normalMap: LoadTextureWrapper(^".artifacts/old_car_n.png\0"),
  emissionMap: LoadTextureWrapper(^".artifacts/old_car_e.png\0"),
  textureTiling: CreateVector2(0.5, 0.5)
}

gui::material::light 1, { x: -1.0, y: 1.0, z: -2.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FFFF, 4.0
gui::material::light 1, { x: 2.0, y: 1.0, z: 1.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FFFF, 4.0
gui::material::light 1, { x: -2.0, y: 1.0, z: 1.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FFFF, 4.0
gui::material::light 1, { x: 1.0, y: 1.0, z: -2.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FFFF, 4.0

gui::window::add cube, cube2

gui::events.on 'loop', (time) ->
  # cube.rot.x += 0.1

rew::channel::timeout 1, -> gui::loop::run(0, 1000 / 400)
