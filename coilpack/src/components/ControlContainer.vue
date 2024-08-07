<script setup lang="ts">
import { Color } from '../types/control'
import controlContainerColors from '../styles/controlContainerColors'

interface IProps {
  color: Color
  width: number
  height: number
  circleLayout?: boolean
}

const props = withDefaults(defineProps<IProps>(), {
  color: Color.default,
  width: 1,
  height: 2
})

const gridClasses: { width: any; height: any } = {
  width: {
    1: 'grid-cols-12',
    2: 'grid-cols-[repeat(24,1fr)]',
    circle: 'grid-cols-10'
  },
  height: {
    1: 'grid-rows-[repeat(6,1fr)]',
    2: 'grid-rows-[repeat(12,1fr)]',
    circle: 'grid-rows-[repeat(10,1fr)]'
  }
}

// Only allow circle layout on 1x2 (small square) tiles.
const colClass =
  props.circleLayout && props.width === 1 && props.height === 2
    ? gridClasses.width.circle
    : gridClasses.width[props.width]
const rowClass =
  props.circleLayout && props.width === 1 && props.height === 2
    ? gridClasses.height.circle
    : gridClasses.height[props.height]
</script>

<template>
  <div>
    <div
      class="controlContainer grid h-full gap-2 rounded-2xl p-3 squircle-2xl @squircle:rounded-none md:rounded-3xl"
      :class="[controlContainerColors[color], colClass, rowClass]"
    >
      <slot />
    </div>
    <div
      class="absolute top-full w-full translate-y-2 select-none overflow-hidden text-ellipsis whitespace-nowrap text-center text-xs font-semibold tracking-wide text-container-foreground"
    >
      <slot name="header" />
    </div>
  </div>
</template>
