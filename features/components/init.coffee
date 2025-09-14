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



gui::components:: = [
  import './button.coffee'
  import './label.coffee'
  import './checkbox.coffee'
  import './dropdown.coffee'
  import './groupbox.coffee'
  import './labelbutton.coffee'
  import './listview.coffee'
  import './panel.coffee'
  import './progressbar.coffee'
  import './scrollpanel.coffee'
  import './slider.coffee'
  import './spinner.coffee'
  import './statusbar.coffee'
  import './tabbar.coffee'
  import './textbox.coffee'
  import './toggle.coffee'
  import './model.coffee'
  import './light.coffee'
  import './rect.coffee'
  import './text.coffee'
].reduce (acc, item) ->
  { ...acc, ...item }

