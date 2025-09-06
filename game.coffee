package gui;

# STD Libraries
import "./_std.coffee!";

# Main Libraries
import "./features/consts.coffee";
import "./features/utils.coffee";
import raylib from "./features/ffi/def.coffee";
gui::raylib = raylib;

import "./features/loop.coffee";
import "./features/window.coffee";
import "./features/components/init.coffee";
import "./features/drawer.coffee";

using namespace rew::ns
using namespace raylib



# gui::events::setOnStart ->

#   rew::channel::timeout 1000, ->
#     gui::loop::stop()

gui::window::init("Hello!")
gui::window::background 0xFF000000

rect = gui::components::Rectangle::new(100, gui::window::height/2, 20, 20, 0xFF0000FF)
scoreText = gui::components::Text::new("0", 1, 1, 0xFF00FF00)
fps = gui::components::Text::new("0", 20, gui::window::height - 20, 0xFF00FF00, 10)
# button = gui::components::Button::new text: "ss"

obstacles = []

gui::window::add rect, scoreText, fps

addNew = ->
  full_height = gui::window::height
  first = full_height - randFrom(full_height/3, full_height/2)
  second = (full_height - first) - 100

  f = gui::components::Rectangle::new(gui::window::width, 0, 100, first)
  s = gui::components::Rectangle::new(gui::window::width, first + 100, 100, second)
  f.type = 'top'
  s.type = 'bottom'

  obstacles.push(f, s)
  gui::window::add(f, s)

frames = 0
intrt = rew::channel::interval 1000, ->
  fps.text = "#{frames}"
  frames = 0



gui::events.on 'resize', () ->
  rect.y = gui::window::height/2
  fps.y = gui::window::height - 20

gui::events.on 'quit', () ->
  rew::channel::intervalClear intrt

gap = 0
nextGap = 200
score = 0
gui::events.on 'loop', (time) ->
  frames++

  if IsKeyDown gui::consts::KEY_DOWN
    rect.y += 1
  else if IsKeyDown gui::consts::KEY_UP
    rect.y -= 1

  gap++

  if gap > nextGap
    addNew()
    gap = 0
    nextGap = randFrom 200, 300

  obstacles.forEach (o) =>
    o.x -= 200 * time

    if CheckCollisionRecsWrapper o.getRect(), rect.getRect()
      rect.freeRect()
      o.freeRect()
      rew::channel::intervalClear intrt
      gui::window::close()

    rect.freeRect()
    o.freeRect()

    if o.x < rect.x and o.type == 'top' and !o.scored
      score += 1
      scoreText.text = "#{score}"
      o.scored = true

    if o.x <= -100
      o.remove()
      obstacles.splice(obstacles.indexOf(o), 1)

rew::channel::timeout 1, -> gui::loop::run(0, 1000 / 400)
