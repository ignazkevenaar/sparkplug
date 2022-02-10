<script setup>
defineProps({
  text: {
    type: String,
    default: ""
  }
})
</script>

<template>
  <div class="flex select-none items-center lg:h-28">
    <slot name="beforeText" />
    <h1 class="grow font-header text-lg font-semibold 2xl:text-xl">
      {{ text }}
    </h1>
    <slot />
  </div>
</template>
