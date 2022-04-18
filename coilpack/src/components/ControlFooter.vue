<script setup>
import packageJSON from '../../package.json';
const version = packageJSON.version;
</script>

<template>
  <footer class="lo:opacity-0 flex select-none items-center gap-2 font-header text-xs md:hidden">
    <mdicon
      name="sparkplug"
      class="-mr-2"
    />
    <span>Sparkplug</span>
    <div class="h-0.5 grow bg-foreground-700" />
    <span class="font-light text-foreground-500">{{ version }}</span>
  </footer>
</template>
