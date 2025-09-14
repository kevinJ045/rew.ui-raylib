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
using namespace raylib



# gui::events::setOnStart ->

#   rew::channel::timeout 1000, ->
#     gui::loop::stop()

gui::window::init("Hello!", gui::consts::FLAG_MSAA_4X_HINT)
gui::window::background 0xFF000000

gui::window::createCamera()
gui::window::camera_orbital = true

# gui::shadow::setAmbientIntensity 1.0
# gui::shadow::init()
# gui::shadow::setAmbient [1.0, 1.0, 1.0, 0.1]


# cube2 = gui::components::Model::from '.artifacts/plane.glb'
# cube2.pos.y = -0.1
# cube2.scale.x = 5
# cube2.scale.y = 5
# cube2.scale.z = 5

# cube = gui::components::Model::from '.artifacts/old_car_new.glb'
# cube.scale.x = 0.25
# cube.scale.y = 0.25
# cube.scale.z = 0.25

# cube2.mat {
#   albedo: 0xFFFFFFFF,
#   roughness: 0.1,
#   metallic: 0.8,
#   occlusion: 1.0,
#   emission: 0xFF000000,

#   emissiveIntensity: 0.0,

#   albedoMap: LoadTextureWrapper(^".artifacts/road_a.png\0"),
#   metalMap: LoadTextureWrapper(^".artifacts/road_mra.png\0"),
#   normalMap: LoadTextureWrapper(^".artifacts/road_n.png\0"),
#   textureTiling: CreateVector2(0.5, 0.5)
# }

# cube.mat {
#   albedo: 0xFFFFFFFF,
#   roughness: 0.0,
#   metallic: 1.0,
#   occlusion: 1.0,
#   emission: 0xFF000000,
  
#   emissiveIntensity: 0.0,

#   albedoMap: LoadTextureWrapper(^".artifacts/old_car_d.png\0"),
#   metalMap: LoadTextureWrapper(^".artifacts/old_car_mra.png\0"),
#   normalMap: LoadTextureWrapper(^".artifacts/old_car_n.png\0"),
#   emissionMap: LoadTextureWrapper(^".artifacts/old_car_e.png\0"),
#   textureTiling: CreateVector2(0.5, 0.5)
# }

# gui::material::light 1, { x: -1.0, y: 1.0, z: -1.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FFFF, 4.0
# # gui::material::light 1, { x: 2.0, y: 1.0, z: 1.0 }, { x: 0, y: 0, z: 0 }, 0xFF00FF00, 3.3
# gui::material::light 1, { x: -0.5, y: 0.5, z: 0.5 }, { x: 0, y: 0, z: 0 }, 0xFF3729E6, 8.3
# # gui::material::light 1, { x: 1.0, y: 1.0, z: -1.0 }, { x: 0, y: 0, z: 0 }, 0xFFFF0000, 2.0

# actualCube = gui::components::Model::cube 1, 1, 1

# # actualCube.pos.x = -2
# actualCube.pos.y = 0.5
# # actualCube.pos.z = -3

# fBase = TG_Voronoi 1024, 1024, 10, 300
# t = new Float32Array([
#   0.00, 1.00
# ])
# colors = new Uint8Array([
#   255, 0, 0, 255,
#   0, 255, 0, 255
# ])
# rockRamp = CreateColorStopsFromArrays 2, &t, &colors
# texAlbedo = TG_AlbedoFromField ImageCopyWrapper(fBase), rockRamp, 2

# fMetal = TG_Checker(1024,1024,16,16);
# fRough = TG_Gradient(1024,1024,true);
# fAO    = ImageCopyWrapper(fBase);
# texMRA = TG_MRAFromFields(fMetal, fRough, fAO);

# texNormal = TG_NormalFromHeight(ImageCopyWrapper(fBase), 4.0);

# actualCube.mat {
#   albedo: 0xFFFFFFFF,
#   roughness: 0.1,
#   metallic: 0.8,
#   occlusion: 1.0,
#   emission: 0xFFFFFFFF,

#   emissiveIntensity: 0.0,

#   albedoMap: texNormal,
#   metalMap: LoadTextureWrapper(^".artifacts/road_mra.png\0"),
#   normalMap: LoadTextureWrapper(^".artifacts/road_n.png\0"),
#   # emissionMap: texAlbedo,
#   textureTiling: CreateVector2(0.5, 0.5),
# }

c = gui::components::Model::from '.artifacts/plane.glb'

c.mat {
  albedoColor: 0xFFFFFFFF,
  albedoTexture: LoadTextureWrapper(^".artifacts/road_a.png\0")
  normalTexture: LoadTextureWrapper(^".artifacts/road_n.png\0")
  ormTexture: LoadTextureWrapper(^".artifacts/road_mra.png\0")
#   roughness: 0.0,
#   metallic: 1.0,
#   occlusion: 1.0,
#   albedoMap: LoadTextureWrapper(^".artifacts/old_car_d.png\0"),
#   metalMap: LoadTextureWrapper(^".artifacts/old_car_mra.png\0"),
#   normalMap: LoadTextureWrapper(^".artifacts/old_car_n.png\0"),
#   emissionMap: LoadTextureWrapper(^".artifacts/old_car_e.png\0"),
}

al = R3D_CreateLightWrapper 2
R3D_SetLightActiveWrapper(al, true);
R3D_SetLightPositionWrapper al, CreateVector3 0, 10, 0
R3D_SetLightColorWrapper al, 0xFF00FF00
R3D_SetLightEnergyWrapper al, 4.0

light = R3D_CreateLightWrapper 0
R3D_SetLightDirectionWrapper(light, CreateVector3(-1, -1, -1));
R3D_SetLightActiveWrapper(light, true);

gui::window::add c

gui::events.on 'loop', (time) ->

  # DrawTextureWrapper texNormal, 0, 0, 0xFFFFFFFF
  # cube.rot.x += 0.1

rew::channel::timeout 1, -> gui::loop::run(0, 1000 / 400)
