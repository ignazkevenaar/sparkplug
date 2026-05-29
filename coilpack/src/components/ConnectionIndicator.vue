<script setup lang="ts">
defineProps<{
  status: boolean
}>()
</script>

<template>
  <div
    class="mt-1 h-1 w-8 rounded-full"
    :class="status ? 'bg-green-highlight' : 'bg-red-highlight'"
  />
</template>
