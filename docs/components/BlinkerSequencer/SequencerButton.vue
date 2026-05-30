<template>
  <button type="button">
    <slot />
  </button>
</template>

<style lang="css" scoped>
button {
  padding: 0 8px;
  border: 1px solid oklch(43.5% 0.029 321.78);
  border-radius: 5px;
  background: oklch(36.4% 0.029 323.89);
  will-change: transform;
  display: flex;
  align-items: center;
  gap: 4px;

  &:enabled:hover {
    background: oklch(43.5% 0.029 321.78);
  }

  &:enabled:active {
    translate: 0 1px;
  }
}
</style>
