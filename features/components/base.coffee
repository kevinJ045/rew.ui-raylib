
using namespace rew::ns;

function Component(type = '2d', extends_fn = null)
  if typeof type == 'function'
    extends_fn = type
    type = extends_fn::_type
  @{macro}
  function Component__Macro(name, fn, ...args)
    fn::_children = [];
    fn::_type = type;

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
      if i > -1 then this.parent._children.splice(
        i
      )

    return proto.class(extends_fn)(name, fn)

export { Component };