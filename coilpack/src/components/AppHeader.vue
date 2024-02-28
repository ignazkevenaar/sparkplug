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
    class="pointer-events-none sticky top-0 z-10 mx-auto w-full p-6 lg:container md:px-8 md:pb-8 lg:h-32 lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
  >
    <div
      class="mask-image absolute inset-0 bg-header-background/50 backdrop-blur-lg"
    />
    <div
      class="text-header-foreground pointer-events-auto relative z-10 flex h-20 w-full items-center justify-between rounded-2xl p-3"
    >
      <HeaderButton
        v-if="showBackButton"
        icon="arrow-left"
        @click="$emit('on-back')"
      />
      <slot v-else name="left" />
      <div class="flex flex-1 select-none flex-col items-center">
        <span
          class="mx-auto flex cursor-pointer items-center transition-opacity"
          @click="$emit('on-logo')"
        >
          <mdicon name="sparkplug" class="w-[24px]" />
          <h1 class="font-header text-lg font-semibold 2xl:text-xl">
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
