
using namespace rew::ns;

function Component(type = '2d', extends_fn = null)
  if typeof type == 'function'
    extends_fn = type
    type = extends_fn::_type
  @{macro}
  function Component__Macro(name, basefn, defaults)


    fn = function ComponentCreator(...args)
      if defaults
        unless args[0]
          args[0] = {}
        args[0] = {
          ...defaults,
          ...args[0]
        }
      basefn.call(this, ...args);

    fn::_children = [];
    fn::_type = type;
    fn::emitter = rew::channel::emitter();

    unless fn::draw
      fn::draw = ->

    _add = if fn::add then fn::add else ->
    fn::add = (...children) ->
      this._children.push(...children)
      children.forEach (child) =>
        child.parent = this
      _add(...children)

    _remove = if fn::remove then fn::remove else ->
    fn::remove = () ->
      i = this.parent._children.indexOf(this)
      if i > -1 then this.parent._children.splice(i, 1)

    return proto.class(extends_fn)(name, fn)

export { Component };