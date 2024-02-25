<script setup>
import colors from "../styles/controlContainerColors";

const props = defineProps({
  color: {
    type: String,
    default: null,
  },
  width: {
    type: Number,
    default: 1,
  },
  height: {
    type: Number,
    default: 2,
  },
  circleLayout: {
    type: Boolean,
    default: false,
  },
});

const gridClasses = {
  width: {
    1: "grid-cols-12",
    2: "grid-cols-[repeat(24,1fr)]",
    circle: "grid-cols-10",
  },
  height: {
    1: "grid-rows-[repeat(6,1fr)]",
    2: "grid-rows-[repeat(12,1fr)]",
    circle: "grid-rows-[repeat(10,1fr)]",
  },
};

// Only allow circle layout on 1x2 (small square) tiles.
const colClass =
  props.circleLayout && props.width === 1 && props.height === 2
    ? gridClasses.width.circle
    : gridClasses.width[props.width];
const rowClass =
  props.circleLayout && props.width === 1 && props.height === 2
    ? gridClasses.height.circle
    : gridClasses.height[props.height];
</script>

<template>
  <div>
    <div
      class="grid h-full gap-2 rounded-2xl p-3 squircle-2xl @squircle:rounded-none md:rounded-3xl"
      :class="[colors[color || 'default'], colClass, rowClass]"
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
