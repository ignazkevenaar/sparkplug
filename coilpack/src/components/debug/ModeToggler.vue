<script setup>
const props = defineProps({
  value: {
    type: Object,
    required: true
  }
});

defineEmits(['input']);
</script>

<template>
  <button
    v-for="(modeState, modeID) in value"
    :key="modeID"
    class="inline-flex gap-1 items-center px-3 m-1 rounded-full border-2 font-semibold"
    :class="modeState ? 'bg-foreground-100 text-black border-foreground-100' : 'text-foreground-200 border-foreground-700'"
    @click="$emit('input', { [modeID]: Number(!modeState) })"
  >
    {{ modeID }}
  </button>
</template>
