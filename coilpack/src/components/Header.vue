<script setup>
defineProps({
  text: {
    type: String,
    default: ""
  }
})
</script>

<template>
  <div class="flex h-20 select-none items-center 2xl:h-40">
    <slot name="beforeText" />
    <h1 class="grow font-header text-lg font-semibold 2xl:text-xl">
      {{ text }}
    </h1>
    <slot />
  </div>
</template>
