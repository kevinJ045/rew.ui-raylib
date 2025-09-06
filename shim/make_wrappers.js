const fs = require("fs");

module.exports = function makeWrappers(name){
  // process.argv[2]

  console.log('Making for', name)

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

    "Texture2D",
    "RenderTexture2D",
    "TextureCubemap",
  ];

  function isStruct(type,name) {
    return name?.startsWith('*') ? false : structs.includes(type.replace(/\s*\*/g, "").trim());
  }

  const functions = [];

  function generateWrapper(decl) {
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
    
    let do_this = false;

    let wrapperReturn = returnType;
    let mallocReturn = false;
    if (isStruct(returnType)) {
      wrapperReturn = returnType + "*";
      mallocReturn = true;
      do_this = true;
    }

    const wrapperParams = paramList.map(p => {
      if (isStruct(p.type, p.name)) {
        do_this = true;
        return `${p.type}* ${p.name}`;
      }
      return p.type + " " + p.name;
    });

    if(do_this){
      functions.push(name);
    } else {
      return "";
    }

    let body = "";
    if (mallocReturn) {
      body += `\t${returnType}* result = malloc(sizeof(${returnType}));\n`;
      body += `\t*result = ${name}(${paramList.map(p => isStruct(p.type, p.name) ? `*${p.name}` : p.name.replace(/\*/g, '')).join(", ")});\n`;
      body += `\treturn result;`;
    } else {
      body += `\t${returnType == "void" ? "" : "return "}${name}(${paramList.map(p => isStruct(p.type, p.name) ? `*${p.name}` : p.name.replace(/\*/g, '')).join(", ")});`;
    }

    return `${wrapperReturn} ${name}Wrapper(${wrapperParams.join(", ")}) {\n${body}\n}\n`;
  }

  const wrappers = declarations.map(generateWrapper).filter(Boolean).join("\n");

  // fs.writeFileSync(`raylib.h/${name}.c`, wrappers);

  return [wrappers, functions];
}