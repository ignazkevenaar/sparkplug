<script setup>
</script>

<template>
  <div>
    <div class="controlGrid relative w-full">
      <div class="innerControlGrid absolute inset-0 grid rounded-2xl bg-background-900 md:rounded-3xl">
        <slot />
      </div>
    </div>
    <div class="my-2 select-none overflow-hidden text-ellipsis whitespace-nowrap text-center text-sm font-semibold tracking-wide lo:text-lightsOut-500">
      <slot name="header" />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.controlGrid {
  $cols: 12;
  $rows: 12;
  $gap: theme('spacing.2');
  $padding: theme('spacing.3');

  padding-top: calc(
    ((100% - (($cols + 1) * $gap)) / $cols) * $rows +
    (($rows + 1) * $gap)
  );

  .innerControlGrid {
    gap: $gap;
    padding: $padding;
    grid-template-columns: repeat($cols, minmax(0, 1fr));
    grid-template-rows: repeat($rows, minmax(0, 1fr));
  }
}
</style>
