<script setup>
import { onMounted, onUnmounted, ref } from 'vue';

let grid = ref(null);
let rowHeight = ref("");
let roGridRowHeight;

const updateGridRowHeight = () => {
  rowHeight.value = window.getComputedStyle(grid.value).gridTemplateColumns.split(' ')[0];
};

onMounted(() => {
  updateGridRowHeight();
  roGridRowHeight = new ResizeObserver(updateGridRowHeight);
  roGridRowHeight.observe(grid.value);
});

onUnmounted(() => {
  if (roGridRowHeight && grid.value) roGridRowHeight.unobserve(grid.value);
});
</script>

<template>
  <div
    class="w-[calc(100vw-theme(spacing.24))] shrink-0 grow-0 md:w-[300px]"
    style="scroll-snap-align: start;"
  >
    <div class="mb-2 items-center font-header font-bold md:flex">
      <slot name="header" />
    </div>
    <div
      v-bind="$attrs"
      ref="grid"
      class="relative grid w-full grid-cols-12 gap-2 rounded-xl"
      :style="`grid-template-rows: repeat(16, ${ rowHeight });`"
    >
      <slot />
    </div>
  </div>
</template>
