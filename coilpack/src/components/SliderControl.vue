<script setup lang="ts">
import { type Ref, computed, onBeforeUnmount, onMounted, ref, watch } from 'vue'
import { Color } from '@/types/control'
import colors from '../styles/controlColors'

const slider: Ref<HTMLDialogElement | undefined> = ref()
const frupske: Ref<HTMLDialogElement | undefined> = ref()
const internalValue = ref(0)
const dragging = ref(false)
const valueStart = ref(0)
const mouseStartY = ref(0)

interface IProps {
  modelValue: number | boolean
  min: number
  max: number
  color?: Color
}

const props = withDefaults(defineProps<IProps>(), {
  min: 0,
  max: 1,
  color: Color.default
})

const emit = defineEmits<{
  'update:modelValue': [modeChange: number | boolean]
}>()

const normalizeValue = (value: number | boolean) => {
  if (typeof value === 'boolean') return Number(value)
  return (value - props.min) / (props.max - props.min)
}

const denormalizeValue = (value: number) => {
  if (typeof value === 'boolean') return Number(value)
  value = Math.max(Math.min(value, 1), 0)
  return Math.round(props.min + value * (props.max - props.min))
}

watch(
  () => props.modelValue,
  async (newValue) => {
    internalValue.value = normalizeValue(newValue)
  },
  { immediate: true }
)

const pointerDownHandler = (event: MouseEvent) => {
  if (!(event.target instanceof Element)) return

  valueStart.value = internalValue.value
  mouseStartY.value = event.clientY
  dragging.value = true
  document.addEventListener('pointermove', pointerMoveHandler)
  document.addEventListener('pointerup', pointerUpHandler)
}

const pointerMoveHandler = (event: MouseEvent) => {
  if (!dragging.value || !(event.target instanceof Element) || !slider.value) return

  const rect: DOMRect = slider.value.getBoundingClientRect()
  const y = (event.clientY - mouseStartY.value) / rect.height
  internalValue.value = Math.max(Math.min(valueStart.value - y, 1), 0)
  emit('update:modelValue', denormalizeValue(internalValue.value))
}

const pointerUpHandler = () => {
  mouseStartY.value = 0
  dragging.value = false

  document.removeEventListener('pointermove', pointerMoveHandler)
  document.removeEventListener('pointerup', pointerUpHandler)
}

onMounted(() => {
  if (!slider.value) return
  slider.value.addEventListener('pointerdown', pointerDownHandler)
  slider.value.addEventListener('wheel', (event) => {
    emit('update:modelValue', denormalizeValue(internalValue.value + (-1 * event.deltaY) / 1000))
  })
})

onBeforeUnmount(() => {
  document.removeEventListener('pointermove', pointerMoveHandler)
  document.removeEventListener('pointerup', pointerUpHandler)
})

const colorClassesBackground = computed(() => {
  return colors.default.background.default
})

const colorClassesHighlight = computed(() => {
  return colors[props.color].background.default
})
</script>

<template>
  <div
    ref="slider"
    class="relative h-full min-h-80 w-40 cursor-pointer touch-none overflow-hidden rounded-3xl"
    :class="colorClassesBackground"
  >
    <div
      ref="frupske"
      class="absolute inset-0 transition-all"
      :class="[colorClassesHighlight, dragging ? 'transition-none' : '']"
      :style="{
        top: `${(1 - internalValue) * 100}%`
      }"
    ></div>
    <span
      class="sticky grid select-none place-items-center p-5 text-lg transition-all"
      :class="dragging ? 'transition-none' : ''"
      :style="{
        top: `${(1 - internalValue) * 100}%`
      }"
    >
      {{ Math.round(internalValue * 100) }}%
    </span>
  </div>
</template>
