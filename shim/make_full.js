
const fs = require("fs");
const makeWrappers = require('./make_wrappers.js');
const makeStruct = require('./make_structs.js');
const getFfiFor = require('./get_ffi_value.js');
const getDeclarations = require('./define_consts.js');

const first = `#include "raylib.h"

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

using namespace rew::ns;

gui::consts:: = {
  ...${getDeclarations('rcore')},
  ...${getDeclarations('rgui')}
}
`);


// fs.writeFileSync('shim/main.c', first + '\n' + structs + '\n\n' + wrappers.join('\n\n'));


// fs.writeFileSync('features/ffi/_values.coffee', `
// func_map = class {
// ${ffi_values.join('\n\n')}
// }

// module.exports = func_map
// `);

