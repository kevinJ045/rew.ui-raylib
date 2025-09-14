
function State(@value)
  @emitter = rew::channel::emitter();

function State::set(val)
  old = @value
  @value = val
  @emitter.emit('change', val, old)
  @

function State::change(fn)
  @emitter.on('change', fn)
  @

function State::clone(fn)
  unless fn
    fn = (a) -> a
  newState = instantiate State
  newState.value = fn @value

  @change (newval) ->
    newState.set(fn newval)

  newState

export { 
  State
}

gui::state = (val) ->
  new State val