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
    class="flex overflow-hidden relative flex-col justify-between p-4 font-semibold bg-background-700 hover:bg-background-600 active:bg-background-800 rounded-2xl cursor-pointer select-none"
    @click="toggled = !toggled"
  >
    <div class="flex justify-between items-center">
      <!-- Blur circle -->
      <div class="absolute -top-8 -left-8 w-16 h-16 bg-current rounded-full opacity-50 blur-2xl" />

      <!-- Icon -->
      <div class="my-2 w-8 h-8 bg-current rounded" />

      <!-- Switch -->
      <div
        class="flex p-0.5 w-10 h-6 rounded-full transition-all"
        :class="toggled ? [ 'bg-background-100' ] : [ 'bg-background-500' ]"
      >
        <div
          class="transition-all"
          :class="toggled ? [ 'flex-1' ] : ''"
        />
        <div
          class="box-border h-full bg-background-700 rounded-full aspect-square"
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
