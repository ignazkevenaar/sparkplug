<script setup>
import { onBeforeUpdate, ref } from 'vue';
import Button from './Button.vue'
import ControlContainer from './ControlContainer.vue'
import ControlFooter from './ControlFooter.vue'
import ControlGrid from './ControlGrid.vue'
import MinimapItem from './MinimapItem.vue'
import Placeholder from './Placeholder.vue'

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
    class="flex max-w-full gap-1 overflow-x-auto py-2 md:hidden"
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
      class="flex snap-x snap-mandatory scroll-px-6 justify-items-start gap-6 overflow-x-scroll pt-2 md:w-auto md:flex-wrap md:overflow-x-hidden"
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
      <ControlFooter />
    </div>
  </div>
</template>
