import type { InjectionKey, Ref } from 'vue'
import type { ControlConfig } from './types/config'
import type { ControlModel } from './types/types'

export const websocketConnectedKey = Symbol() as InjectionKey<Ref<boolean>>

export const controlsConfigKey = Symbol() as InjectionKey<Ref<ControlConfig>>
export const controlModelsKey = Symbol() as InjectionKey<Ref<ControlModel>>

export const blinkNormalKey = Symbol() as InjectionKey<Ref<boolean>>
export const blinkFastKey = Symbol() as InjectionKey<Ref<boolean>>
