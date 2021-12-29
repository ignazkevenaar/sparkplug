<script setup>
import { ref, onMounted, onUnmounted } from 'vue';

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
    class="grow-0 shrink-0 w-[calc(100vw-theme(spacing.24))] md:w-[300px]"
    style="scroll-snap-align: start;"
  >
    <div class="md:flex items-center mb-2 font-header font-bold">
      <slot name="header" />
    </div>
    <div
      v-bind="$attrs"
      ref="grid"
      class="grid relative grid-cols-12 gap-2 w-full rounded-xl"
      :style="`grid-template-rows: repeat(16, ${ rowHeight });`"
    >
      <slot />
    </div>
  </div>
</template>
