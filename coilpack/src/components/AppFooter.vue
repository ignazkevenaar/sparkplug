<script setup lang="ts">
const version = import.meta.env.VITE_APP_VERSION
const buildDate = import.meta.env.VITE_BUILD_DATE
const formatObj = new Intl.DateTimeFormat('en-US', { dateStyle: 'long', timeStyle: 'short' })
const formattedBuildDate = formatObj.format(new Date(buildDate))
</script>

<template>
  <footer
    class="text-header-foreground pointer-events-none mx-auto flex w-full p-6 text-xs opacity-35 select-none md:px-8 md:pb-8 lg:container lg:h-32 lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
  >
    <div class="mx-auto flex-col justify-center">
      <p class="flex items-center justify-center gap-0.5">
        <mdicon name="sparkplug" size="18" />
        <span>Version {{ version }}</span
        ><br />
      </p>
      <p class="flex items-center justify-center gap-1">Built on {{ formattedBuildDate }}</p>
    </div>
  </footer>
</template>
