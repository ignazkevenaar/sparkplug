<script setup lang="ts">
import { BackgroundStyle, ForegroundStyle } from '@/types/control.icon'
import type { CascadableProperties, IconControl, Position } from '@/types/control.icon'
import { type Ref, computed, inject, ref } from 'vue'
import { Color } from '@/types/control'
import type { ControlModel } from '@/types/types'
import { blinkNormalKey } from '@/provide-keys'
import colors from '../../styles/controlColors'

interface IProps {
  modelValue: ControlModel
  control: IconControl
  type: string
  disabled: boolean
}

const props = withDefaults(defineProps<IProps>(), {
  type: 'button'
})

const emit = defineEmits<{
  'update:modelValue': [modeChange: ControlModel]
}>()

// Animation timers.
const blinkNormal = inject(blinkNormalKey)

const roundClass = computed(() =>
  props.control.round ? 'rounded-full' : 'rounded-xl md:rounded-3xl corner-super-1.5'
)

const currentPositions = computed(() =>
  props.control.positions.flatMap((position, index) => {
    const allModesApply = Object.keys(position.modes).every((mode) => {
      let positionValue = position.modes[mode]
      if (typeof positionValue === 'boolean') positionValue = Number(position.modes[mode]) * 255
      return props.modelValue[mode] === positionValue
    })
    return allModesApply ? [{ ...position, index }] : []
  })
)
const nextPositionIndex = computed(
  () => currentPositions.value[currentPositions.value.length - 1]?.index + 1
)

// Finds 'hold' position that comes later than the highest current position, if any.
const holdPosition = computed(() =>
  props.control.positions
    .slice(nextPositionIndex.value)
    .find((position) => position.type === 'hold')
)

// The pair of slices wraps around the array.
// [3,4,0,1,2]
//      ^
const nonHoldPosition = computed(() =>
  [
    ...props.control.positions.slice(nextPositionIndex.value),
    ...props.control.positions.slice(0, nextPositionIndex.value)
  ].find((position) => position.type !== 'hold')
)

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
  const activeModes = currentPositions.value
    .filter((position) => (!holdingPosition.value ? position.type !== 'hold' : true))
    .filter((position) => !(blinkNormal?.value && position.animation === 'blinking'))

  let mergedProps: CascadableProperties = { ...defaultProperties, ...props.control }

  activeModes.forEach((activeMode) => {
    mergedProps = { ...mergedProps, ...activeMode }
  })

  // Defaults
  // Base control
  // Every active mode
  return mergedProps
})

// TODO: Do variable modes even work!?
const swapSetUnset = (original: ControlModel): ControlModel => {
  const modified = { ...original }
  Object.keys(modified).forEach((key) => {
    modified[key] = !modified[key]
  })
  return modified
}

const colorClasses = computed(() => {
  const backgroundColor = cascadedProps.value.backgroundColor
  const foregroundColor = cascadedProps.value.foregroundColor
  const backgroundStyle = cascadedProps.value.backgroundStyle
  const foregroundStyle = cascadedProps.value.foregroundStyle

  return [
    ...colors.common.background[backgroundStyle],
    ...colors.common.foreground[foregroundStyle],
    ...colors[backgroundColor].background[backgroundStyle],
    ...colors[foregroundColor].foreground[foregroundStyle]
  ]
})

const buttonDown = ref(false)
const initialYCoordinate = ref(0)
const holding = ref(false)
const holdingPosition: Ref<Position | undefined> = ref()
const holdDelay = 150
const holdCancelOffset = 20
const scrollDirty = ref(false)

const pointerDown = (event: PointerEvent) => {
  if (props.control.readOnly) return

  if (typeof TouchEvent !== 'undefined' && event instanceof TouchEvent) {
    initialYCoordinate.value = event.touches[0].clientY
  } else {
    initialYCoordinate.value = event.clientY
  }

  holdTimeout = setTimeout(onHold, holdDelay)
  buttonDown.value = true
}

const cancelHold = () => {
  if (holdingPosition.value) emit('update:modelValue', swapSetUnset(holdingPosition.value.modes))

  holding.value = false
  holdingPosition.value = undefined
}

const pointerUp = () => {
  window.removeEventListener('pointerup', pointerUp)

  if (props.control.readOnly) return

  if (buttonDown.value) buttonDown.value = false
  else return

  clearTimeout(holdTimeout)
  initialYCoordinate.value = 0

  if (holding.value) {
    cancelHold()
    return
  }

  // Send modes of next (or first) non-drag-mode.
  if (!scrollDirty.value && nonHoldPosition.value)
    emit('update:modelValue', nonHoldPosition.value.modes)
  scrollDirty.value = false
}

const pointerMove = (event: PointerEvent) => {
  if (holdTimeout && Math.abs(event.clientY - initialYCoordinate.value) > holdCancelOffset) {
    scrollDirty.value = true
    clearTimeout(holdTimeout)
    cancelHold()
  }
}

let holdTimeout: number

const onHold = () => {
  // So mouse up events temporarily work outside of button bounds.
  window.addEventListener('pointerup', pointerUp)
  holding.value = true

  if (holdPosition.value) {
    holdingPosition.value = holdPosition.value
    emit('update:modelValue', holdPosition.value.modes)
  }
}

const events = computed(() => {
  if (props.disabled || props.control.readOnly) return {}

  return {
    pointerdown: pointerDown,
    pointerup: pointerUp,
    pointermove: buttonDown.value ? pointerMove : null
  }
})
</script>

<template>
  <component
    :is="type === 'button' ? 'button' : 'div'"
    class="relative z-0 flex flex-col items-center justify-center ring-inset enabled:cursor-pointer disabled:opacity-50"
    :class="[roundClass, colorClasses, type]"
    :disabled="disabled || control.readOnly"
    v-on="events"
  >
    <mdicon v-if="cascadedProps.icon" :name="cascadedProps.icon" size="36" />
    <slot />
    <span v-if="cascadedProps.label" class="-mb-2 text-center text-xs select-none md:font-medium">
      {{ cascadedProps.label }}
    </span>
    <div
      v-if="holdPosition || holdingPosition"
      class="absolute bottom-1 h-0.75 w-5 rounded-full bg-current opacity-25"
    />
  </component>
</template>
