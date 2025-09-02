const fs = require("fs");

module.exports = function getDeclarations(name){
  const fstring = fs.readFileSync(`raylib.h/${name}.hpp`, { encoding: 'utf-8' })
    .replace(/\/\/(.+)/g, '');


  const consts = {};

  const matches = fstring.match(/typedef enum \{([^}]+)\}/gm)
  matches.shift()

  if(matches){
    matches.forEach(typedef => {
      let current = 0;
      typedef.split('\n').map(match => {
        const m = match.match(/((\w+)(=(.+),|,|))/g);
        if(m){
          if(m[1]){
            current = parseInt(m[1]);
          }
          consts[m[0].replace(/,$/, '')] = current;
          current += 1;
        }
      });
    });
  }

  return JSON.stringify(consts);
}

