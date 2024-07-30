<script setup lang="ts">
import { controlModelsKey, controlsConfigKey } from '@/provide-keys'
import type { ControlModel } from '@/types/types'
import ControlPanel from '../components/ControlPanel.vue'
import { inject } from 'vue'

const controlsConfig = inject(controlsConfigKey)
const controlModels = inject(controlModelsKey)

defineEmits<{
  'update:modelValue': [modeChange: ControlModel | unknown]
}>()
</script>

<template>
  <div>
    <ControlPanel
      class="mx-auto flex flex-1 flex-col justify-between p-6 pb-2 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-6 lg:px-12 lg:pb-12 xl:px-20 xl:pb-10"
      :modelValue="controlModels"
      :control-config="controlsConfig?.status"
      @update:modelValue="$emit('update:modelValue', $event)"
    />
    <ControlPanel
      class="mx-auto flex flex-1 flex-col justify-between bg-controls-background p-6 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-8 lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
      :modelValue="controlModels"
      :control-config="controlsConfig?.controls"
      @update:modelValue="$emit('update:modelValue', $event)"
    />
  </div>
</template>
