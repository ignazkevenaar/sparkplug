import type { Color, Control } from './control'
import type { ControlModel } from './types'

export enum BackgroundStyle {
  default = 'default',
  outline = 'outline',
  fill = 'fill'
}

export enum ForegroundStyle {
  default = 'default',
  highlight = 'highlight',
  dim = 'dim'
}

export interface CascadableProperties {
  icon: string
  backgroundStyle: BackgroundStyle
  foregroundStyle: ForegroundStyle
  backgroundColor: Color
  foregroundColor: Color
  animation: string
  label: string
}

export interface Position extends CascadableProperties {
  modes: ControlModel
  type: string
}

export interface IconControl extends Control, CascadableProperties {
  round: boolean
  positions: Position[]
  readOnly: boolean
}
