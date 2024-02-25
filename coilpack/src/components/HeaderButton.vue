<script setup>
defineProps({
  icon: {
    type: String,
    default: null,
  },
});
</script>

<template>
  <button class="rounded-full border-2 border-stone-800 p-3 hover:bg-stone-900">
    <mdicon v-if="icon" :name="icon" class="w-[24px] text-foreground-100" />
    <slot />
  </button>
</template>
