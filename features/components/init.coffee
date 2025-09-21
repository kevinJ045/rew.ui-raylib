package gui::components;

# import { Button } from './button.coffee'
# import { Label } from './label.coffee'
# import { CheckBox } from './checkbox.coffee'
# import { Dropdown } from './dropdown.coffee'
# import { GroupBox } from './groupbox.coffee'
# import { LabelButton } from './labelbutton.coffee'
# import { ListView } from './listview.coffee'
# import { Panel } from './panel.coffee'
# import { ProgressBar } from './progressbar.coffee'
# import { ScrollPanel } from './scrollpanel.coffee'
# import { Slider } from './slider.coffee'
# import { Spinner } from './spinner.coffee'
# import { StatusBar } from './statusbar.coffee'
# import { TabBar } from './tabbar.coffee'
# import { TextBox } from './textbox.coffee'
# import { Toggle } from './toggle.coffee'
# import { Model } from './model.coffee'
# import { Light } from './light.coffee'
# import { Rect } from './rect.coffee'
# import { Text } from './text.coffee'
# import { Circle } from './circle.coffee'
# import { Line } from './line.coffee'
# import { Grid } from './grid.coffee'
# import { Group } from './group.coffee'


gui::components:: = [
  import './rect.coffee'
  import './text.coffee'
  import './flex_rect.coffee'
  import './flex_text.coffee'
].reduce (acc, item) ->
  { ...acc, ...item }

