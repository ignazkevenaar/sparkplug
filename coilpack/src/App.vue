<script setup lang="ts">
import * as api from './api.js'
import type { ControlConfig, SparkplugConfig } from './types/config'
import { type Ref, onMounted, provide, ref } from 'vue'
import {
  blinkFastKey,
  blinkNormalKey,
  controlModelsKey,
  controlsConfigKey,
  websocketConnectedKey
} from './provide-keys'
import AppFooter from './components/AppFooter.vue'
import AppHeader from './components/AppHeader.vue'
import AppRouter from './components/AppRouter.vue'
import ConnectionIndicator from './components/ConnectionIndicator.vue'
import type { ControlModel } from './types/types'
import ErrorMessage from './components/ErrorMessage.vue'
import HeaderButton from './components/HeaderButton.vue'
import LoadingIndicator from './components/LoadingIndicator.vue'
import { loadConfiguration } from './config.js'

const loading = ref(true)
const error: Ref<Error | null> = ref(null)
const lightsOut = ref(false)
const currentRoute = ref('/')
const websocketConnected = ref(false)

const config: Ref<SparkplugConfig | null> = ref(null)
const lightingModes: Ref<string[]> = ref([])
const controlsConfig: Ref<ControlConfig> = ref({ status: [], controls: [] })
const controlModels: Ref<ControlModel> = ref({})

provide(controlsConfigKey, controlsConfig)
provide(controlModelsKey, controlModels)
provide(websocketConnectedKey, websocketConnected)

const navigateHome = () => {
  window.location.href = '#/'
}
const scollToTop = () => {
  window.scrollTo({ top: 0, left: 0, behavior: 'smooth' })
}

const groupAndSetModeChanges = (event: ControlModel) => {
  const setModeStrings: string[] = []
  const unsetModeStrings: string[] = []

  Object.keys(event).forEach((modeID) => {
    let newValue = event[modeID]
    if (typeof newValue === 'boolean') newValue = Number(newValue) * 255

    if (import.meta.env.DEV) {
      // Don't wait for websocket confirmation when debugging.
      controlModels.value[modeID] = newValue
    }

    const modeIndex: number = lightingModes.value.indexOf(modeID)
    if (modeIndex > -1) {
      if (newValue === 255) setModeStrings.push(modeIndex.toString())
      else if (newValue === 0) unsetModeStrings.push(modeIndex.toString())
      else setModeStrings.push(`${modeIndex}:${newValue}`)
    }
  })

  if (setModeStrings.length) api.setMode(setModeStrings)
  if (unsetModeStrings.length) api.unsetMode(unsetModeStrings)
}

const unsetAllModes = () => {
  api.unsetAllModes()

  if (import.meta.env.DEV) {
    lightingModes.value.forEach((mode) => {
      controlModels.value[mode] = 0
    })
  }
}

const onGetMode = (inputArguments: string[]) => {
  inputArguments.forEach((argument) => {
    const [modeIndex, modeState] = argument.split(':')
    const modeID = lightingModes.value[parseInt(modeIndex)]
    controlModels.value[modeID] = parseInt(modeState)
  })
}

const setupWebsocket = async () => {
  await api
    .setup()
    .then(() => {
      api.onGetMode(onGetMode)

      api.connection.onopen = () => {
        websocketConnected.value = true

        // Get initial mode state.
        api.getModes()
      }

      api.connection.onclose = () => {
        websocketConnected.value = false
        setupWebsocket()
      }
    })
    .catch((reason: Error) => (error.value = reason))
}

onMounted(async () => {
  const loadedConfig = await loadConfiguration().catch((reason) => {
    error.value = reason
  })
  if (!loadedConfig) return

  config.value = loadedConfig.config
  lightingModes.value = loadedConfig.lightingModes
  controlsConfig.value = loadedConfig.controlsConfig

  controlModels.value = {}
  loadedConfig.lightingModes.forEach((mode) => {
    controlModels.value[mode] = 0
  })

  if (config.value?.name) {
    document.title = `Sparkplug — ${config.value.name}`
  }

  await setupWebsocket()

  loading.value = false
})

// Animation timers for controls.
const blinkNormal = ref(false)
setInterval(() => {
  blinkNormal.value = !blinkNormal.value
}, 300)
provide(blinkNormalKey, blinkNormal)

const blinkFast = ref(false)
setInterval(() => {
  blinkFast.value = !blinkFast.value
}, 150)
provide(blinkFastKey, blinkFast)
</script>

<template>
  <div :class="[lightsOut ? 'lightsOut' : '']" class="relative min-h-screen bg-app-background">
    <AppHeader
      :show-back-button="currentRoute != '' && currentRoute != '/'"
      :subtitle="config?.name"
      :show-buttons="!error && !loading"
      @on-back="navigateHome"
      @on-logo="scollToTop"
    >
      <template #left>
        <HeaderButton icon="weather-night" @click="lightsOut = !lightsOut" />
      </template>
      <template #right>
        <HeaderButton icon="power-standby" :disabled="!websocketConnected" @click="unsetAllModes" />
      </template>
      <ConnectionIndicator :status="websocketConnected" />
    </AppHeader>
    <Transition mode="out-in">
      <div
        v-if="error"
        class="absolute inset-0 grid place-items-center p-6 pb-2 lg:container md:px-8 md:pb-6 lg:px-12 lg:pb-12 xl:px-20 xl:pb-10"
      >
        <ErrorMessage :error="error" />
      </div>
      <div v-else-if="loading" class="absolute inset-0 grid place-items-center">
        <LoadingIndicator />
      </div>
      <AppRouter
        v-else
        @route-changed="currentRoute = $event"
        @update:modelValue="groupAndSetModeChanges"
      />
    </Transition>
    <AppFooter />
  </div>
</template>
