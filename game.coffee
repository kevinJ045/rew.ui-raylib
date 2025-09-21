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
# import "./features/components/init.coffee";
# import "./features/drawer.coffee";
# import { calculateLayout } from "./features/layout.coffee";

using namespace rew::ns
using namespace raylib


gui::window::init("Hello Flex Layout!")
gui::window::background 0xFF181818

# Create a root flex container
root = gui::components::FlexRect::new {
  x: 0,
  y: 0,
  width: gui::window::width,
  height: gui::window::height,
  flexDirection: 'column',
  color: 0x00000000
}
gui::window::add(root)

# Create a header
header = gui::components::FlexRect::new {
  height: 50,
  color: 0xFF303030,
  flexDirection: 'row',
  alignItems: 'center',
  padding: 10
}
root.add(header)

title = gui::components::FlexText::new {
    text: "My App",
    fontSize: 20,
    color: 0xFFFFFFFF,
    margin: 10
}
header.add(title)

# Create a main content area
main = gui::components::FlexRect::new {
  flexGrow: 1,
  color: 0x00000000,
  flexDirection: 'row'
}
root.add(main)

# A sidebar
sidebar = gui::components::FlexRect::new {
  width: 200,
  color: 0xFF252525,
  flexDirection: 'column',
  alignItems: 'center',
  justifyContent: 'flex-start',
  padding: 10
}
main.add(sidebar)

button1 = gui::components::FlexRect::new { width: 180, height: 40, color: 0xFF404040, margin: 10 }
button2 = gui::components::FlexRect::new { width: 180, height: 40, color: 0xFF404040, margin: 10 }
sidebar.add(button1, button2)


# The main content
content = gui::components::FlexRect::new {
  flexGrow: 1,
  color: 0xFF181818,
  justifyContent: 'center',
  alignItems: 'center',
  flexDirection: 'column'
}
main.add(content)

welcomeText = gui::components::FlexText::new {
    text: "Welcome to the new layout system!",
    fontSize: 24,
    color: 0xFFFFFFFF,
    margin: 20
}
content.add(welcomeText)

grower = gui::components::FlexRect::new {
    width: 100,
    height: 50,
    flexGrow: 1,
    color: 0xFF505080,
    margin: 10
}
content.add(grower)


gui::events.on 'loop', (time) ->
  calculateLayout(root)

rew::channel::timeout 1, -> gui::loop::run(60)
