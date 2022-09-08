<script setup>
import { onBeforeUpdate, ref } from 'vue';
import Button from './Button.vue'
import ControlContainer from './ControlContainer.vue'
import ControlFooter from './ControlFooter.vue'
import Placeholder from './Placeholder.vue'

defineProps({
  value: {
    type: Object,
    required: true
  },
  controlConfig: {
    type: Array,
    required: true
  }
});

defineEmits(['input'])

const controlToComponent = {
  'placeholder': Placeholder,
  'button': Button
};

// Automatic control panel grid sizing.

// 2*theme(spacing.6) - Horizontal padding.
// theme(spacing.4) - Horizontal grid gap.

const autoCols = [
  "grid-cols-[repeat(2,calc((100vw-2*theme(spacing.6)-theme(spacing.4))/2))]",
  "sm:grid-cols-[repeat(2,200px)]",
];

// theme(spacing.10) vertical grid gap.

const autoRows = [
  "auto-rows-[calc(((100vw-2_*_theme(spacing.6)_-_theme(spacing.4))/2_-_theme(spacing.10))/2)]",
  "sm:auto-rows-[calc((200px_-_theme(spacing.10))/2)]",
];
</script>

<template>
  <div>
    <div
      class="controlGrid grid w-full gap-4 gap-y-10 pb-10 xl:gap-10"
      :class="[autoCols, autoRows]"
    >
      <ControlContainer
        v-for="(item, itemIndex) in controlConfig"
        :key="itemIndex"
        :color="item.color"
        class="relative"
        :width="item.width"
        :height="item.height"
        :circle-layout="item.circleLayout"
        :style="{ 'grid-area': `span ${ item.height ?? 2 } / span ${ item.width ?? 1 } / span ${ item.height ?? 2 } / span ${ item.width ?? 1 }` }"
      >
        <component
          :is="controlToComponent[control.type.toLowerCase()]"
          v-for="(control, controlIndex) in item.controls"
          :key="controlIndex"
          :value="value"
          :style="{ 'grid-area': `${ control.top ?? 'auto' } / ${ control.left ?? 'auto' } / span ${ control.height ?? 1 } / span ${ control.width ?? 1 }` }"
          :control="control"
          @input="$emit('input', $event)"
        >
          {{ control.text }}
        </component>
        <template #header>
          {{ item.name }}
        </template>
      </ControlContainer>
    </div>
    <ControlFooter class="pt-4" />
  </div>
</template>
