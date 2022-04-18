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
</script>

<template>
  <div>
    <div
      class="grid w-full grid-cols-2 gap-3"
    >
      <ControlContainer
        v-for="(item, itemIndex) in controlConfig"
        :key="itemIndex"
        class="max-w-[200px]"
      >
        <component
          :is="controlToComponent[control.type.toLowerCase()]"
          v-for="(control, controlIndex) in item.controls"
          :key="controlIndex"
          :value="value"
          :style="{ 'grid-area': `${ control.left ?? 'auto' } / ${ control.top ?? 'auto' } / span ${ control.height ?? 1 } / span ${ control.width ?? 1 }` }"
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
