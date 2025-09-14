import "#std.testing!";


using (
  import "./main.coffee!"
)


App("title") myApp = ->
  Scene {
    orbitCamera: true
  }, [
    Light {
      direction: [-1, -1, -1],
      shadow: true
    }
    Light {
      type: 'omni'
    }

    Rect {
      w: 100,
      h: 100,
      x: 100,
      y: 100,
      color: 0xFF00FF00
    }

    Model {
      model: 'cube',
      size: 1,
      mat: {
        albedoColor: 0xFF00FF00,
        roughness: 1.0,
        metalness: 1.0,
        occlusion: 1.0
      }
    }

    Model {
      model: '.artifacts/plane.glb',
      scale: {
        x: 5,
        y: 1,
        z: 5
      }
      pos: {
        x: 0,
        y: -1,
        z: 0,
      }
      mat: {
        albedoColor: 0xFFFFFFFF,
        albedoTexture: ".artifacts/road_a.png",
        normalTexture: ".artifacts/road_n.png",
        ormTexture: ".artifacts/road_mra.png",
        roughness: 1.0,
        metalness: 1.0,
        occlusion: 1.0
      }
    }

  ]

startApp myApp