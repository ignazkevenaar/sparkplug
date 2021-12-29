<script setup>
import { ref, onBeforeUpdate } from 'vue';
import ControlContainer from './ControlContainer.vue'
import ControlGrid from './ControlGrid.vue'
import MinimapItem from './MinimapItem.vue'

import Placeholder from './Placeholder.vue'
import Button from './Button.vue'

const props = defineProps({
  value: {
    type: Object,
    required: true
  },
  controlConfig: {
    type: Object,
    required: true
  },
  paddingSides: {
    type: String,
    default: ""
  },
  paddingBottom: {
    type: String,
    default: ""
  },
});

defineEmits(['input'])

const currentYear = new Date().getFullYear();

const controlToComponent = {
  'placeholder': Placeholder,
  'button': Button
};

let selectedMinimapItems = ref(Array(props.controlConfig.length).fill(false));
let containerRefs = [];
let containerObservers = [];
let minimapRefs = [];

const setContainerRef = el => {
  if (!el) return;
  let newIndex = containerRefs.length;
  containerRefs.push(el);

  const io = new IntersectionObserver(entries => {
    entries.forEach(entry => {
      // if (entry.isIntersecting) {
      //   minimapRefs[newIndex].$el.scrollIntoView({ behavior: "smooth" });
      // }
      selectedMinimapItems.value[newIndex] = entry.isIntersecting;
    });
  }, {
    threshold: 1
  });
  io.observe(el.$el);
  containerObservers.push(io);
}

const setMinimapRef = el => { minimapRefs.push(el); };

onBeforeUpdate(() => {
  containerRefs = [];
  containerObservers = [];
  minimapRefs = [];
});

const scrollToContainer = categoryIndex => {
  containerRefs[categoryIndex].$el.scrollIntoView({ behavior: "smooth" });
};
</script>

<template>
  <!-- Minimap -->
  <div
    class="flex md:hidden overflow-x-auto gap-1 py-2 max-w-full"
    :class="paddingSides"
  >
    <MinimapItem
      v-for="(category, categoryIndex) in controlConfig"
      :key="category.name"
      :ref="setMinimapRef"
      :selected="selectedMinimapItems[categoryIndex]"
      :icon="category.icon"
      @click="scrollToContainer(categoryIndex)"
    />
  </div>
  <div>
    <div
      class="flex overflow-x-scroll md:overflow-x-hidden md:flex-wrap gap-6 justify-items-start pt-2 md:w-auto scroll-px-6 snap-x snap-mandatory"
      :class="[paddingSides, paddingBottom]"
    >
      <ControlContainer
        v-for="category in controlConfig"
        :key="category.name"
        :ref="setContainerRef"
      >
        <template #header>
          {{ category.name }}
        </template>

        <component
          :is="controlToComponent[control.type.toLowerCase()]"
          v-for="(control, controlIndex) in category.controls"
          :key="controlIndex"
          :value="value"
          :style="{ 'grid-column': control.grid.column, 'grid-row': control.grid.row }"
          :control="control"
          @input="$emit('input', $event)"
        >
          {{ control.text }}
        </component>
      </ControlContainer>
    </div>
  </div>
</template>

<style lang="scss" scoped>
  footer {
    writing-mode: vertical-rl;
    text-orientation: mixed;
  }
</style>
