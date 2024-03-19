import type { Color, Control } from './control'
import type { ControlModel } from './types'

export enum Style {
  stroke = 'stroke',
  fill = 'fill'
}

export interface CascadableProperties {
  color: Color
  style: Style
}

export interface State extends CascadableProperties {
  modes: ControlModel
}

export interface Segment extends CascadableProperties {
  selector: string
  states: State[]
}

export interface DisplayControl extends Control {
  path: string
  segments: Segment[]
}
