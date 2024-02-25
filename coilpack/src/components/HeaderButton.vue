<script setup>
defineProps({
  icon: {
    type: String,
    default: null
  }
});
</script>

<template>
  <button
    class="hover:bg-stone-900 rounded-full p-3 border-2 border-stone-800"
  >
    <mdicon
      v-if="icon"
      :name="icon"
      class="text-foreground-100 w-[24px]"
    />
    <slot />
  </button>
</template>
