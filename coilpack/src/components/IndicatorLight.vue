<script setup>
import { computed } from 'vue';

const props = defineProps({
  value: {
    type: Object,
    required: true
  },
  indicator: {
    type: Object,
    required: true
  }
});

const onClasses = computed(() => {
  const onClassSet = new Set();

  for (const [key, value] of Object.entries(props.indicator.set))
    if (key in props.value && props.value[key] > 0)
      onClassSet.add([...value.split(' '), `on-${key}`]);

  return Array.from(onClassSet);
});
</script>

<template>
  <mdicon
    :name="indicator.icon"
    :class="[indicator.color, onClasses]"
    class="fill blink"
  />
</template>
