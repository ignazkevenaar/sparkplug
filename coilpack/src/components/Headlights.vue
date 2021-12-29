<script setup>
import Ring from './Ring.vue'
</script>

<template>
  <div class="flex overflow-hidden justify-center px-4 bg-background-800 bg-gradient-to-br from-background-800 to-background-700 rounded-lg">
    <div class="relative top-[10%] self-center w-3/5 bg-background-600 rounded-full border-8 border-black aspect-square">
      <Ring
        class="absolute inset-[-1.25rem]"
        :start-angle="0"
        :percent="25"
        :stroke-width="2"
      />

      <div class="absolute left-1/2 h-full -rotate-90 -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded rotate-90" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full rotate-[-120deg] -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded rotate-[120deg]" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full rotate-[30deg] -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded rotate-[-30deg]" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full rotate-[60deg] -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded rotate-[-60deg]" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full rotate-90 -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 w-6 h-6 bg-foreground-50 rounded rotate-[-90deg]" />
          <div class="mx-auto w-2 h-2 bg-foreground-300 rounded-full" />
        </div>
      </div>

      <div class="absolute left-1/2 w-2 h-6 bg-foreground-50 rounded-full -translate-x-1/2 translate-y-4" />
      <!-- <slot /> -->
    </div>
  </div>
</template>
