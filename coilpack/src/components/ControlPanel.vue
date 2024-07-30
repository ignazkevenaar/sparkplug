<script setup lang="ts">
import type { ControlContainer } from '../types/control'
import ControlContainerComponent from './ControlContainer.vue'
import type { ControlModel } from '@/types/types'
import DisplayControl from './controls/DisplayControl.vue'
import IconControl from './controls/IconControl.vue'
import Placeholder from './controls/PlaceholderControl.vue'
import { inject } from 'vue'
import { websocketConnectedKey } from '../provide-keys'

defineProps<{
  modelValue: ControlModel | undefined
  controlConfig: ControlContainer[] | undefined
}>()

defineEmits<{
  'update:modelValue': [modeChange: ControlModel | unknown]
}>()

const controlToComponent = {
  placeholder: Placeholder,
  button: IconControl,
  indicator: IconControl,
  display: DisplayControl
}

const websocketConnected = inject(websocketConnectedKey)

// Automatic control panel grid sizing.
const autoCols = [
  'grid-cols-[repeat(2,calc((100vw-2*theme(spacing.6)-var(--gap-controls-x))/2))]',
  'sm:grid-cols-[repeat(2,200px)]'
]

const autoRows = [
  'auto-rows-[calc(((100vw-2_*_theme(spacing.6)_-_var(--gap-controls-x))/2_-_var(--gap-controls-y))/2)]',
  'sm:auto-rows-[calc((200px_-_var(--gap-controls-y))/2)]'
]
</script>

<template>
  <div>
    <div
      class="controlGrid grid w-full gap-x-controls-x gap-y-controls-y pb-10 xl:gap-10"
      :class="[autoCols, autoRows]"
    >
      <ControlContainerComponent
        v-for="(item, itemIndex) in controlConfig"
        :key="itemIndex"
        :color="item.color"
        class="relative"
        :width="item.width"
        :height="item.height"
        :circle-layout="item.circleLayout"
        :style="{
          'grid-area': `span ${item.height ?? 2} / span ${item.width ?? 1} / span ${item.height ?? 2} / span ${item.width ?? 1}`
        }"
      >
        <component
          :is="controlToComponent[control.type]"
          v-for="(control, controlIndex) in item.controls"
          :key="controlIndex"
          :modelValue="modelValue"
          :style="{
            'grid-area': `${control.top ?? 'auto'} / ${control.left ?? 'auto'} / span ${control.height ?? 1} / span ${control.width ?? 1}`
          }"
          :control="control"
          :type="control.type"
          :disabled="!websocketConnected"
          @update:modelValue="$emit('update:modelValue', $event)"
        />
        <template #header>
          {{ item.name }}
        </template>
      </ControlContainerComponent>
    </div>
  </div>
</template>
