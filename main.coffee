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

#declare* "=state" = state; 
#declare* "=App" = App; 

GUI = Usage::create (ctx) ->
  ctx.state = gui::state;
  ctx.using(ctx.namespace(gui::consts::))
  Object.keys(gui::components::).forEach (key) ->
    ctx[key] = function(props, children)
      if Array.isArray(props)
        children = props
        props = {}
      
      unless children
        children = []

      gui::components::[key]::new {
        ...props,
        children
      }
  
  on3d = false
  ctx.Scene = (props, items) ->
    gui::window::createCamera()

    if Array.isArray(props)
      items = props
      props = {}
    on3d = true
    
    if props.camerapos
      gui::window::setCameraPosition ...props.camerapos

    if props.orbitCamera
      gui::window::camera_orbital = true

    items.filter (item) ->
      item?._type !== 'light'

  ctx.Board = (items) ->
    items

  ctx.Model = (props, children) ->
    m = gui::components::Model::from props.model, {
      ...props,
      children
    }
    if props.mat
      m.mat props.mat
    m
  
  ctx.Light = (props) ->
    props = {
      type: 'dir',
      ...props
    }
    props.type = if props.type == 'dir'
      then 0 else if props.type == 'spot'
      then 1 else 2
    l = gui::components::Light::new(props.type)

    if props.pos
      l.move(...props.pos)
    
    if props.range
      l.range(props.range)

    if props.specular
      l.specular(props.specular)

    if props.color
      l.color(props.color)
    
    if props.direction
      l.direct(...props.direction)
    
    if props.shadow
      l.shadowOn(props.shadow == true ? 1024 : props.shadow)
    
    unless props.disable
      l.enable()

  ctx.bg = (col) ->
    gui::window::background col

  ctx.startApp = (app, frames) ->
    app()
    rew::channel::timeout 1, -> gui::loop::run(0, frames || 1000 / 400)

  ctx.App = (title, flags, fn) ->
    unless fn
      fn = flags
      flags = {}
    
    -> {
      gui::window::init(title, flags.winmode or gui::consts::FLAG_WINDOW_RESIZABLE);

      if flags.3d or on3d
        gui::window::createCamera()

      if flags.orbit_camera
        gui::window::camera_orbital = true

      gui::window::add ...fn.call(gui::events)
    }



GUI.gui = gui;

module.exports = GUI;