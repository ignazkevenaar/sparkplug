<script setup lang="ts">
defineProps<{
  status: boolean
}>()
</script>

<template>
  <div class="mt-1 h-1 w-8 rounded-full" :class="status ? 'bg-lime-500' : 'bg-red-500'" />
</template>
