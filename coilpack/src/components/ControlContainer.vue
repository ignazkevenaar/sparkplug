<script setup lang="ts">
import { Color } from '../types/control'
import controlContainerColors from '../styles/controlContainerColors'

interface IProps {
  color: Color
  width: 1 | 2
  height: 1 | 2
  circleLayout?: boolean
}

const props = withDefaults(defineProps<IProps>(), {
  color: Color.default,
  width: 1,
  height: 2
})

interface gridClass {
  1: string
  2: string
  circle: string
}

const gridClasses: { width: gridClass; height: gridClass } = {
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
      class="controlContainer corner-super-[1.2] xs:rounded-4xl grid h-full gap-1.5 rounded-3xl p-2"
      :class="[controlContainerColors[color], colClass, rowClass]"
    >
      <slot />
    </div>
    <div
      class="absolute top-full w-full translate-y-2 overflow-hidden text-center text-xs font-semibold tracking-wide text-ellipsis whitespace-nowrap select-none"
      :class="controlContainerColors.foreground"
    >
      <slot name="header" />
    </div>
  </div>
</template>
