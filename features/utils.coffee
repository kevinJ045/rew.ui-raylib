package gui::utils;

function utils::isVec3(item)
  item?.x and item?.y and item?.z

function utils::toVec3A(item)
  {
    x: item[0],
    y: item[2],
    z: item[3]
  }

function utils::vec3(...args)
  utils::toVec3A args
  
function utils::checkVec3(c, n, x, y, z)
  if x?
    c[n].x = x
  if y?
    c[n].y = y
  if z?
    c[n].z = z

function utils::vec3ptr(thing)
  gui::raylib.CreateVector3 thing.x, thing.y, thing.z