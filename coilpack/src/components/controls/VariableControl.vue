<script setup lang="ts">
import { BackgroundStyle, ForegroundStyle } from '@/types/control.icon'
import type { CascadableProperties, VariableControl } from '@/types/control.icon'
import { computed, ref } from 'vue'
import { Color } from '@/types/control'
import type { ControlModel } from '@/types/types'
import SliderControl from '../SliderControl.vue'
import SparkDialog from '../SparkDialog.vue'
import colors from '../../styles/controlColors'
import throttle from 'lodash/throttle'

interface IProps {
  value: ControlModel
  control: VariableControl
}

const props = withDefaults(defineProps<IProps>(), {})

const emit = defineEmits<{
  input: [modeChange: ControlModel]
}>()

const defaultProperties: CascadableProperties = {
  backgroundStyle: BackgroundStyle.default,
  backgroundColor: Color.default,
  foregroundColor: Color.default,
  foregroundStyle: ForegroundStyle.default,
  animation: '',
  label: '',
  icon: ''
}

// Cascade properties from props, active positions.
// Conditionally filters hold positions when not holding.
// Filters cascaded null properties.
const cascadedProps = computed<CascadableProperties>(() => {
  let mergedProps: CascadableProperties = { ...defaultProperties, ...props.control }

  // Defaults
  // Base control
  // Every active mode
  return mergedProps
})

const roundClass = computed(() =>
  props.control.round
    ? 'rounded-full'
    : 'rounded-lg md:rounded-2xl @squircle:squircle-xl @squircle:!rounded-none'
)

const backdropColorClasses = computed(() => {
  const foregroundColor = cascadedProps.value.foregroundColor
  const backgroundStyle = cascadedProps.value.backgroundStyle
  const foregroundStyle = cascadedProps.value.foregroundStyle

  return [
    ...colors.common.background[backgroundStyle],
    ...colors.common.foreground[foregroundStyle],
    ...colors.default.background[backgroundStyle],
    ...colors[foregroundColor].foreground[foregroundStyle]
  ]
})

const sliderColorClasses = computed(() => {
  const backgroundStyle = cascadedProps.value.backgroundStyle
  const backgroundColor = cascadedProps.value.backgroundColor

  return [...colors[backgroundColor].background[backgroundStyle]]
})

const dialog = ref(false)

const currentValue = computed(() => {
  return props.value[props.control.mode]
})

// Throttle...
const doIt = throttle((value) => {
  emit('input', { [props.control.mode]: value })
}, 100)

const innerSliderStyles = computed(() => {
  const currentModeValue = props.value[props.control.mode]
  if (typeof currentModeValue === 'number') {
    return {
      top: `${100 - (currentModeValue * 100) / 255}%`
    }
  } else if (typeof currentModeValue === 'boolean') {
    return {
      display: currentModeValue ? undefined : 'none'
    }
  }
  return {}
})

const emitOpposite = () => {
  const currentValue = props.value[props.control.mode]
  if (currentValue === 0) emit('input', { [props.control.mode]: 255 })
  else emit('input', { [props.control.mode]: 0 })
}
</script>

<template>
  <button
    class="button relative z-0 flex select-none flex-col items-center justify-center overflow-hidden bg-gradient-to-br p-2 text-center text-xs ring-inset enabled:cursor-pointer disabled:opacity-50 md:text-sm md:font-semibold"
    :class="[roundClass, backdropColorClasses]"
    :disabled="control.readOnly"
    @click="dialog = true"
  >
    <div
      :class="sliderColorClasses"
      class="absolute inset-0 -z-10 transition-all"
      :style="innerSliderStyles"
    ></div>
    <mdicon v-if="cascadedProps.icon" :name="cascadedProps.icon" size="36" />
    <slot />
    {{ cascadedProps.label }}
    <SparkDialog v-model="dialog" :title="cascadedProps.label" class="cursor-default">
      <SliderControl
        :model-value="currentValue"
        @update:model-value="doIt"
        :min="0"
        :max="255"
        class="mx-auto"
        :color="cascadedProps.backgroundColor"
      />
      <button
        class="bg-button-background hover:enabled:bg-button-background-hover mx-auto mt-8 block rounded-full p-4"
        @click="emitOpposite"
      >
        <mdicon name="PowerCycle" size="36" />
      </button>
    </SparkDialog>
  </button>
</template>
