<script setup>
defineProps({
  error: {
    type: Object,
    required: true,
  },
});
</script>

<template>
  <div
    class="flex flex-col items-center gap-3 font-mono font-bold text-red-500 drop-shadow-[0_0_25px_rgba(255,0,0,0.5)]"
  >
    <mdicon name="sparkplug-sad" size="48" class="ml-2" />
    <div class="bg-current px-1">
      <span class="uppercase text-black">Error</span>
    </div>
    <div>
      {{ error.message }}
    </div>
  </div>
</template>
