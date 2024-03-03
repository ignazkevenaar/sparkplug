<script setup>
import HeaderButton from "./HeaderButton.vue";

defineProps({
  status: {
    type: Boolean,
    default: false,
  },
});
</script>

<template>
  <div
    class="mt-1 h-1 w-8 rounded-full"
    :class="
      status
        ? 'bg-control-foreground-green-highlight'
        : 'bg-control-foreground-red-highlight'
    "
  />
</template>
