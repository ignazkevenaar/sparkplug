import type { ControlContainer } from './control'

export interface SparkplugConfig {
  name: string
}

export interface ControlConfig {
  status?: ControlContainer[]
  controls?: ControlContainer[]
}
