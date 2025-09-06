
const fs = require("fs");
const makeWrappers = require('./make_wrappers.js');
const makeStruct = require('./make_structs.js');
const getFfiFor = require('./get_ffi_value.js');
const getDeclarations = require('./define_consts.js');

const first = `#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdlib.h>`;


const nodes = fs.readdirSync('raylib.h')
  .filter(i => i.endsWith('.h') && i !== "structs.h")
  .map(i => makeWrappers(i.replace(/\.h$/, '')));

const wrappers = nodes.map(i => i[0])
const functions = nodes.map(i => i[1])

const ffi_values = fs.readdirSync('raylib.h')
  .filter(i => i.endsWith('.h') && i !== "structs.h")
  .map(i => getFfiFor(i.replace(/\.h$/, ''), functions.flat()));

const structs = makeStruct();

fs.writeFileSync('features/consts.coffee', `
package gui::consts;

gui::consts:: = {
  FLAG_VSYNC_HINT         : 0x00000040,   
  FLAG_FULLSCREEN_MODE    : 0x00000002,   
  FLAG_WINDOW_RESIZABLE   : 0x00000004,   
  FLAG_WINDOW_UNDECORATED : 0x00000008,   
  FLAG_WINDOW_HIDDEN      : 0x00000080,   
  FLAG_WINDOW_MINIMIZED   : 0x00000200,   
  FLAG_WINDOW_MAXIMIZED   : 0x00000400,   
  FLAG_WINDOW_UNFOCUSED   : 0x00000800,   
  FLAG_WINDOW_TOPMOST     : 0x00001000,   
  FLAG_WINDOW_ALWAYS_RUN  : 0x00000100,   
  FLAG_WINDOW_TRANSPARENT : 0x00000010,   
  FLAG_WINDOW_HIGHDPI     : 0x00002000,   
  FLAG_WINDOW_MOUSE_PASSTHROUGH : 0x00004000, 
  FLAG_BORDERLESS_WINDOWED_MODE : 0x00008000, 
  FLAG_MSAA_4X_HINT       : 0x00000020,   
  FLAG_INTERLACED_HINT    : 0x00010000,
  ...${getDeclarations('rcore')},
  ...${getDeclarations('rgui')}
}
`);


fs.writeFileSync('shim/main.c', first + '\n' + structs + '\n\n' + wrappers.join('\n\n'));


fs.writeFileSync('features/ffi/_values.coffee', `
func_map = class {
${ffi_values.join('\n\n')}
}

module.exports = func_map
`);

