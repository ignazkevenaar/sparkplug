<script setup>
import packageJSON from '../../package.json';
const version = packageJSON.version;
</script>

<template>
  <footer class="flex items-center gap-2 font-header">
    <mdicon name="sparkplug" />
    <span>Sparkplug</span>
    <span class="font-light text-foreground-500">{{ version }}</span>
    <div class="w-px grow bg-foreground-500" />
    <span>&copy;{{ new Date().getFullYear() }}</span>
  </footer>
</template>

<style lang="scss" scoped>
  footer {
    writing-mode: vertical-lr;
    text-orientation: mixed;
  }
</style>
