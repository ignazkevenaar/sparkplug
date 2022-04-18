<script setup>
import Ring from './Ring.vue'
</script>

<template>
  <div class="flex justify-center overflow-hidden rounded-lg bg-background-800 bg-gradient-to-br from-background-800 to-background-700 px-6">
    <div class="relative top-[10%] aspect-square w-3/5 self-center rounded-full border-8 border-black bg-background-600">
      <Ring
        class="absolute inset-[-1.25rem]"
        :start-angle="0"
        :percent="25"
        :stroke-width="2"
      />

      <div class="absolute left-1/2 h-full -translate-x-1/2 -rotate-90">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rotate-90 rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2 rotate-[-120deg]">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rotate-[120deg] rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2 rotate-[30deg]">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rotate-[-30deg] rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2 rotate-[60deg]">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rotate-[-60deg] rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>
      <div class="absolute left-1/2 h-full -translate-x-1/2 rotate-90">
        <div class="-translate-y-14">
          <div class="mb-2 h-6 w-6 rotate-[-90deg] rounded bg-foreground-50" />
          <div class="mx-auto h-2 w-2 rounded-full bg-foreground-300" />
        </div>
      </div>

      <div class="absolute left-1/2 h-6 w-2 -translate-x-1/2 translate-y-4 rounded-full bg-foreground-50" />
      <!-- <slot /> -->
    </div>
  </div>
</template>
