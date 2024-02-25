<script setup>
import HeaderButton from './HeaderButton.vue'

defineProps({
  showBackButton: {
    type: Boolean,
    default: false
  },
  subtitle: {
    type: String,
    default: null
  }
});

defineEmits(['on-back', 'on-logo']);
</script>

<template>
  <header class="bg-header-background pointer-events-none sticky top-0 z-10 w-full">
    <div class="w-full mx-auto flex h-28 items-center px-6 md:px-8 lg:container lg:h-32 lg:px-12 xl:px-20 justify-between pointer-events-auto">
      <HeaderButton
        v-if="showBackButton"
        icon="arrow-left"
        @click="$emit('on-back')"
      />
      <slot
        v-else
        name="left"
      />
      <div class="flex-1 flex flex-col items-center">
        <span
          class="mx-auto flex items-center transition-opacity lo:opacity-0"
          @click="$emit('on-logo')"
        >
          <mdicon
            name="sparkplug"
            class="text-foreground-400 w-[24px]"
          />
          <h1 class="select-none font-header text-lg font-semibold 2xl:text-xl">
            Sparkplug
          </h1>
        </span>
        <span
          v-if="subtitle?.length > 0"
          class="mx-auto text-xs opacity-25 font-semibold"
        >
          {{ subtitle }}
        </span>
      </div>
      <slot name="right" />
    </div>
  </header>
</template>
