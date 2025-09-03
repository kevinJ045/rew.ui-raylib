package gui::events;

using namespace rew::ns;
using namespace gui::raylib;
using namespace gui::consts::;

mainEvents = {}

# Priority 1 Events
# Cannot be propagated or stopped
eventsP1 = rew::channel::emitter()


# Priority 2 Events
# Can be propagated or stopped
eventsP2 = rew::channel::emitter()

mainEvents._beforeQuit = ->
  let stop = false;
  eventsP2.emit('beforeQuit', { keepLoop: -> stop = true })
  eventsP1.emit('beforeQuit', { keepLoop: -> stop = true })
  stop
  

mainEvents._onQuit = ->
  eventsP2.emit('onQuit')
  eventsP1.emit('onQuit')

mainEvents._onStart = ->
  eventsP2.emit('start')
  eventsP1.emit('start')

mainEvents._loop = (time) ->
  eventsP2.emit('loop', time)
  eventsP1.emit('loop', time)

gui::events = eventsP2;

export { mainEvents, listener: eventsP1 }
