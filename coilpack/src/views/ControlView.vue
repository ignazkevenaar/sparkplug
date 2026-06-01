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
      class="m-3 bg-black pb-0"
      :modelValue="controlModels"
      :control-config="controlsConfig?.status"
      @update:modelValue="$emit('update:modelValue', $event)"
    />
    <ControlPanel
      class="m-3 pb-0"
      :modelValue="controlModels"
      :control-config="controlsConfig?.controls"
      @update:modelValue="$emit('update:modelValue', $event)"
    />
  </div>
</template>
