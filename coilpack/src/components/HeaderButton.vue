<script setup lang="ts">
defineProps<{
  icon?: string
}>()
</script>

<template>
  <button
    class="rounded-full border-2 border-header-controls/50 p-3 enabled:active:bg-header-controls/15 disabled:opacity-50"
  >
    <mdicon v-if="icon" :name="icon" class="w-[24px] text-header-foreground" />
    <slot />
  </button>
</template>
