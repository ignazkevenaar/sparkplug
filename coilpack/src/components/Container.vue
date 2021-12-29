<script setup>
import { ref, onMounted } from 'vue'

defineProps({
  width: {
    type: String,
    default: ""
  },
  padding: {
    type: String,
    default: ""
  },
});

const content = ref(null);
const hasScrolled = ref(false);

onMounted(() => {
  const ob = new IntersectionObserver(payload => { hasScrolled.value = !payload[0].isIntersecting});
  ob.observe(content.value);
});
</script>

<template>
  <div
    class="block md:grid min-w-0 min-h-0"
    style="grid-template-rows: min-content minmax(0, 1fr);"
  >
    <div
      class="hidden md:block"
      :class="[width, padding, hasScrolled ? 'border-b border-background-700 shadow-lg z-10' : null]"
    >
      <slot name="header" />
    </div>
    <div
      class="overflow-y-auto h-full"
      :class="[width]"
    >
      <div
        ref="content"
        class="h-0"
      >
        <!-- Hidden element for scrolled detection -->
      </div>
      <slot />
    </div>
  </div>
</template>
