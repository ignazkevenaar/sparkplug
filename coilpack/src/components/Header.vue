<script setup>
defineProps({
  text: {
    type: String,
    default: ""
  }
})
</script>

<template>
  <div class="flex items-center h-20 2xl:h-40 select-none">
    <slot name="beforeText" />
    <h1 class="grow font-header text-lg 2xl:text-xl font-semibold">
      {{ text }}
    </h1>
    <slot />
  </div>
</template>
