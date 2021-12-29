<script setup>

defineProps({
  selected: Boolean,
  icon: {
    type: String,
    default: null
  }
});

const selectedClasses = "bg-foreground-100 border-0 delay-100";
const selectedIconClasses = "text-black";
</script>

<template>
  <button
    class="grid shrink-0 place-items-center w-12 h-8 rounded-full border-[1.5px] border-background-600 transition-all"
    :class="[selected ? selectedClasses : null]"
  >
    <mdicon
      v-if="icon"
      :name="icon"
      class="transition-all delay-100"
      :class="[selected ? selectedIconClasses : 'text-foreground-500']"
    />
  </button>
</template>
