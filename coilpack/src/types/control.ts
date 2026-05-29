export enum Color {
  default = 'default',
  transparent = 'transparent',
  black = 'black',
  red = 'red',
  yellow = 'yellow',
  green = 'green',
  blue = 'blue',
  pink = 'pink'
}

export interface ControlContainer {
  controls: Control[]
  name: string
  width: 1 | 2
  height: 1 | 2
  color: Color
  circleLayout: boolean
}

export enum ControlType {
  placeholder = 'placeholder',
  button = 'button',
  indicator = 'indicator',
  display = 'display'
}

export interface Control {
  type: ControlType
  width: number
  height: number
  top: number
  left: number
  color: Color
}
