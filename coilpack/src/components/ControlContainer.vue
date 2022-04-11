<script setup>
const props = defineProps({
  height: {
    type: Number,
    default: 4
  }
});
</script>

<template>
  <div>
    <div
      v-bind="$attrs"
      class="controlGrid relative w-full"
    >
      <div class="innerControlGrid absolute inset-0 grid rounded-2xl bg-black md:rounded-3xl">
        <slot />
      </div>
    </div>
    <div class="flex items-center overflow-hidden text-ellipsis whitespace-nowrap text-xl font-bold">
      <slot name="header" />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.controlGrid {
  $cols: 4;
  $rows: v-bind('props.height');
  $gap: theme('spacing.2');


  padding-top: calc(
    ((100% - (($cols + 1) * $gap)) / $cols) * $rows +
    (($rows + 1) * $gap)
  );

  .innerControlGrid {
    gap: $gap;
    padding: $gap;
    grid-template-columns: repeat($cols, minmax(0, 1fr));
    grid-template-rows: repeat($rows, minmax(0, 1fr));
  }
}
</style>
