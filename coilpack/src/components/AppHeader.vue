<script setup>
defineProps({
  showBackButton: {
    type: Boolean,
    default: false
  }
});

defineEmits(['on-back', 'on-logo']);
</script>

<template>
  <header class="pointer-events-none sticky top-0 z-10 w-full">
    <div class="mx-auto flex h-20 items-center px-6 md:px-8 lg:container lg:h-32 lg:px-12 xl:px-20">
      <div class="pointer-events-auto flex items-center">
        <button
          v-if="showBackButton"
          class="rounded-full p-3 hover:bg-background-700"
          @click="$emit('on-back')"
        >
          <mdicon
            name="arrow-left"
            class="w-[24px] text-foreground-400"
          />
        </button>
        <span
          class="flex items-center transition-opacity lo:opacity-0"
          @click="$emit('on-logo')"
        >
          <mdicon
            name="sparkplug"
            class="w-[24px] text-foreground-400"
          />
          <h1 class="select-none font-header text-lg font-semibold 2xl:text-xl">
            Sparkplug
          </h1>
        </span>
      </div>
    </div>
  </header>
</template>
