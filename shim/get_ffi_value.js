const fs = require("fs");

module.exports = function getFfiFor(name, functions){

  const declarations = fs.readFileSync(`raylib.h/${name}.h`, { encoding: 'utf-8' }).split('\n')
    .filter(i => !!i.trim())
    .filter(i => !i.startsWith('//'))
    .map(i => i.replace(/\/\/(.+)/, ''));

  const structs = [
    "Vector2",
    "Vector3",
    "Vector4",
    "Matrix",
    // "Color",
    "Rectangle",

    "Image",
    "Texture",
    "RenderTexture",
    "NPatchInfo",
    "GlyphInfo",
    "Font",

    "Camera",
    "Camera2D",
    "Camera3D",

    "Shader",
    "MaterialMap",
    "Material",
    "Mesh",
    "Model",
    "ModelAnimation",
    "Transform",
    "BoneInfo",
    "Ray",
    "RayCollision",
    "BoundingBox",

    "Wave",
    "AudioStream",
    "Sound",
    "Music",

    "VrDeviceInfo",
    "VrStereoConfig",

    "FilePathList",

    "AutomationEvent",
    "AutomationEventList",
  ];

  function isStruct(type,name) {
    return name?.startsWith('*') ? false : structs.includes(type.replace(/\s*\*/g, "").trim());
  }

  function getType(type){
    switch(type){
      case "int":
        return 'rew::ffi::i32'
      case "unsigned int":
        return 'rew::ffi::u32'
      case "bool":
        return 'rew::ffi::bool'
      case "float":
        return 'rew::ffi::f32'
      case "long":
        return 'rew::ffi::i64'
      case "Color":
        return 'rew::ffi::i64'
      default:
        return 'rew::ffi::buffer'
    };
  }

  function generateFuncMaps(decl) {
    decl = decl.trim().replace(/;$/, "");

    const [returnType, rest] = decl.split(/\s+(.+)/);

    const match = rest.match(/^(\w+)\((.*)\)$/);
    if (!match) return null;

    const name = match[1];
    const params = match[2].trim();

    let paramList = [];
    if (params !== "void" && params !== "") {
      paramList = params.split(",").map(p => {
        const parts = p.trim().split(/\s+/);
        const type = parts.slice(0, -1).join(" ");
        const paramName = parts[parts.length - 1];
        return { type, name: paramName };
      });
    }

    let wrapperReturn = getType(returnType);
    if (isStruct(returnType)) {
      wrapper = true;
      wrapperReturn = 'rew::ffi::ptr';
    }

    const wrapperParams = paramList.map(p => {
      if (isStruct(p.type, p.name)) {
        wrapper = true;
        return `rew::ffi::ptr`;
      }
      return getType(p.type);
    });

    return `\tffi_type(${wrapperParams}) ${name}${functions.includes(name) ? 'Wrapper' : ''} = -> ${wrapperReturn}`;
  }

  const funcmaps = declarations.map(generateFuncMaps).filter(Boolean).join("\n");
  return funcmaps;
}