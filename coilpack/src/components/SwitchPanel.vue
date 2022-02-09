<script setup>
import { ref } from 'vue';
// const props = defineProps({
//   round: Boolean,
//   icon: Boolean
// })

const toggled = ref(false);
</script>

<template>
  <div
    class="relative flex cursor-pointer select-none flex-col justify-between overflow-hidden rounded-2xl bg-background-700 p-4 font-semibold hover:bg-background-600 active:bg-background-800"
    @click="toggled = !toggled"
  >
    <div class="flex items-center justify-between">
      <!-- Blur circle -->
      <div class="absolute -top-8 -left-8 h-16 w-16 rounded-full bg-current opacity-50 blur-2xl" />

      <!-- Icon -->
      <div class="my-2 h-8 w-8 rounded bg-current" />

      <!-- Switch -->
      <div
        class="flex h-6 w-10 rounded-full p-0.5 transition-all"
        :class="toggled ? [ 'bg-background-100' ] : [ 'bg-background-500' ]"
      >
        <div
          class="transition-all"
          :class="toggled ? [ 'flex-1' ] : ''"
        />
        <div
          class="box-border aspect-square h-full rounded-full bg-background-700"
        />
        <div
          class="transition-all"
          :class="toggled ? '' : [ 'flex-1' ]"
        />
      </div>
    </div>
    <div class="font-semibold">
      <slot />
    </div>
  </div>
</template>
