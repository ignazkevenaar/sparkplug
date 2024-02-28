<script setup>
defineProps({
  icon: {
    type: String,
    default: null,
  },
});
</script>

<template>
  <button
    class="border-header-controls/50 active:bg-header-controls/15 rounded-full border-2 p-3"
  >
    <mdicon v-if="icon" :name="icon" class="text-header-foreground w-[24px]" />
    <slot />
  </button>
</template>
