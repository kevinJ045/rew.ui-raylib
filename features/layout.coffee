export calculateLayout = (component, parentLayout) ->
  # If no parent layout is provided, use the component's props as the base.
  if parentLayout?
    parentLayout = parentLayout._layout
  parentLayout ||= { x: component.props.x or 0, y: component.props.y or 0, width: component.props.width || 0, height: component.props.height || 0 }

  # Handle padding
  padding = component.props.padding or 0
  paddedLayout = {
    x: parentLayout.x + padding,
    y: parentLayout.y + padding,
    width: parentLayout.width - (padding * 2),
    height: parentLayout.height - (padding * 2)
  }
  # Assign the calculated layout to the component.
  component._layout = paddedLayout

  # If the component has children, calculate their layout.
  if component.children and component.children.length > 0
    flexDirection = component.props.flexDirection or 'row'

    if flexDirection == 'row'
      calculateRowLayout(component, paddedLayout)
    else
      calculateColumnLayout(component, paddedLayout)

calculateRowLayout = (component, parentLayout) ->
  children = component.children
  justifyContent = component.props.justifyContent or 'flex-start'
  alignItems = component.props.alignItems or 'stretch'

  totalChildrenWidth = children.reduce((sum, child) -> sum + (child.props.width or 0) + ((child.props.margin or 0) * 2), 0)
  totalFlexGrow = children.reduce((sum, child) -> sum + (child.props.flexGrow or 0), 0)
  remainingSpace = parentLayout.width - totalChildrenWidth

  currentX = parentLayout.x

  if justifyContent == 'flex-end'
    currentX += remainingSpace
  else if justifyContent == 'center'
    currentX += remainingSpace / 2

  spacing = 0
  if justifyContent == 'space-between'
    spacing = remainingSpace / (children.length - 1)
  else if justifyContent == 'space-around'
    spacing = remainingSpace / children.length
    currentX += spacing / 2

  for child in children
    margin = child.props.margin or 0
    flexGrow = child.props.flexGrow or 0
    growWidth = 0
    if totalFlexGrow > 0 and remainingSpace > 0
      growWidth = (remainingSpace * flexGrow) / totalFlexGrow

    childWidth = (child.props.width or 0) + growWidth
    childHeight = child.props.height or 0

    childX = currentX + margin
    childY = parentLayout.y + margin
    if alignItems == 'flex-end'
      childY = parentLayout.y + parentLayout.height - childHeight - margin
    else if alignItems == 'center'
      childY = parentLayout.y + (parentLayout.height - childHeight) / 2
    
    childLayout =
      x: childX
      y: childY
      width: childWidth
      height: if alignItems == 'stretch' then parentLayout.height - (margin * 2) else childHeight

    calculateLayout(child, childLayout)

    currentX += childWidth + (margin * 2) + spacing

calculateColumnLayout = (component, parentLayout) ->
  children = component.children
  justifyContent = component.props.justifyContent or 'flex-start'
  alignItems = component.props.alignItems or 'stretch'

  totalChildrenHeight = children.reduce((sum, child) -> sum + (child.props.height or 0) + ((child.props.margin or 0) * 2), 0)
  totalFlexGrow = children.reduce((sum, child) -> sum + (child.props.flexGrow or 0), 0)
  remainingSpace = parentLayout.height - totalChildrenHeight

  currentY = parentLayout.y

  if justifyContent == 'flex-end'
    currentY += remainingSpace
  else if justifyContent == 'center'
    currentY += remainingSpace / 2

  spacing = 0
  if justifyContent == 'space-between'
    spacing = remainingSpace / (children.length - 1)
  else if justifyContent == 'space-around'
    spacing = remainingSpace / children.length
    currentY += spacing / 2

  for child in children
    margin = child.props.margin or 0
    flexGrow = child.props.flexGrow or 0
    growHeight = 0
    if totalFlexGrow > 0 and remainingSpace > 0
      growHeight = (remainingSpace * flexGrow) / totalFlexGrow

    childWidth = child.props.width or 0
    childHeight = (child.props.height or 0) + growHeight

    childX = parentLayout.x + margin
    childY = currentY + margin
    if alignItems == 'flex-end'
      childX = parentLayout.x + parentLayout.width - childWidth - margin
    else if alignItems == 'center'
      childX = parentLayout.x + (parentLayout.width - childWidth) / 2

    childLayout =
      x: childX
      y: childY
      width: if alignItems == 'stretch' then parentLayout.width - (margin * 2) else childWidth
      height: childHeight

    calculateLayout(child, childLayout)

    currentY += childHeight + (margin * 2) + spacing