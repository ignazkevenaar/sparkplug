<script setup>
import HeaderButton from "./HeaderButton.vue";

defineProps({
  showBackButton: {
    type: Boolean,
    default: false,
  },
  subtitle: {
    type: String,
    default: null,
  },
});

defineEmits(["on-back", "on-logo"]);
</script>

<template>
  <header
    class="pointer-events-none sticky top-0 z-10 w-full bg-header-background"
  >
    <div
      class="pointer-events-auto mx-auto flex h-28 w-full items-center justify-between px-6 lg:container md:px-8 lg:h-32 lg:px-12 xl:px-20"
    >
      <HeaderButton
        v-if="showBackButton"
        icon="arrow-left"
        @click="$emit('on-back')"
      />
      <slot v-else name="left" />
      <div class="flex flex-1 flex-col items-center">
        <span
          class="mx-auto flex items-center transition-opacity"
          @click="$emit('on-logo')"
        >
          <mdicon name="sparkplug" class="w-[24px] text-foreground-200" />
          <h1 class="select-none font-header text-lg font-semibold 2xl:text-xl">
            Sparkplug
          </h1>
        </span>
        <span
          v-if="subtitle?.length > 0"
          class="mx-auto text-xs font-semibold opacity-25"
        >
          {{ subtitle }}
        </span>
      </div>
      <slot name="right" />
    </div>
  </header>
</template>
