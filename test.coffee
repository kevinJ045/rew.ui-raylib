import "#std.testing!";
import ui from "./main.coffee";

using namespace rew::ns;

ui::init(ui::consts::INIT.VIDEO)

win = ui::window::new("SDL Window", "resizable")

renderer = win.createRenderer()

renderer.loadFontForSizes('assets/DejaVuSansMono.ttf', 16, 24, 36)

ui::loop::run ->
  renderer.setRGB()
  renderer.clear()

  renderer.setRGB 255
  renderer.fillRect(100, 100, 100, 100)

  renderer.setFontSize 16
  renderer.drawText 100, 200, "hello"

  renderer.setFontSize 24
  renderer.drawText 100, 300, "hello"

  renderer.setFontSize 36
  renderer.drawText 100, 400, "hello"

  renderer.render()



