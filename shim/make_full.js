
const fs = require("fs");
const makeWrappers = require('./make_wrappers.js');
const makeStruct = require('./make_structs.js');
const getFfiFor = require('./get_ffi_value.js');
const getDeclarations = require('./define_consts.js');

const first = `#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdlib.h>
#include <string.h>

#include "r3d.h"
#include "texture_gen.h"
`;


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
  LIGHTGRAY: 0xFFCCCCCC, // (200,200,200,255)
  GRAY:      0xFF828282, // (130,130,130,255)
  DARKGRAY:  0xFF505050, // (80,80,80,255)
  YELLOW:    0xFF00F9FD, // (253,249,0,255)
  GOLD:      0xFF00CBFF, // (255,203,0,255)
  ORANGE:    0xFF00A1FF, // (255,161,0,255)
  PINK:      0xFFC36DFF, // (255,109,194,255)
  RED:       0xFF3729E6, // (230,41,55,255)
  MAROON:    0xFF2121BE, // (190,33,55,255)
  GREEN:     0xFF30E400, // (0,228,48,255)
  LIME:      0xFF2F9E00, // (0,158,47,255)
  DARKGREEN: 0xFF2C7500, // (0,117,44,255)
  SKYBLUE:   0xFFFFBF66, // (102,191,255,255)
  BLUE:      0xFFF17900, // (0,121,241,255)
  DARKBLUE:  0xFFAC5200, // (0,82,172,255)
  PURPLE:    0xFFFF7AC8, // (200,122,255,255)
  VIOLET:    0xFFBE3C87, // (135,60,190,255)
  DARKPURPLE:0xFF7E1F70, // (112,31,126,255)
  BEIGE:     0xFF83B0D3, // (211,176,131,255)
  BROWN:     0xFF4F6A7F, // (127,106,79,255)
  DARKBROWN: 0xFF2F3F4C, // (76,63,47,255)

  WHITE:     0xFFFFFFFF, // (255,255,255,255)
  BLACK:     0xFF000000, // (0,0,0,255)
  BLANK:     0x00000000, // (0,0,0,0)
  MAGENTA:   0xFFFF00FF, // (255,0,255,255)
  RAYWHITE:  0xFFF5F5F5  // (245,245,245,255)

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
  ...${getDeclarations('r3d')},
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

