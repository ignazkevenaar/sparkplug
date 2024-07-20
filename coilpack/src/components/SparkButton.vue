<script setup lang="ts">
interface IProps {
  disabled?: boolean
}

withDefaults(defineProps<IProps>(), {
  disabled: false
})
</script>

<template>
  <button
    class="select-none rounded-md bg-button-background px-4 py-2 hover:bg-button-background-hover disabled:pointer-events-none disabled:opacity-35"
  >
    <slot></slot>
  </button>
</template>
