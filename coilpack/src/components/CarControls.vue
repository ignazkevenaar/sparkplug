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
  },
  paddingBottom: {
    type: String,
    default: ""
  },
});

defineEmits(['input'])

const controlToComponent = {
  'placeholder': Placeholder,
  'button': Button
};
</script>

<template>
  <div>
    <masonry-wall
      :items="controlConfig"
      :column-width="150"
      :gap="10"
      class="w-full"
    >
      <template #default="{ item }">
        <ControlContainer
          :height="item.height"
        >
          <component
            :is="controlToComponent[control.type.toLowerCase()]"
            v-for="(control, controlIndex) in item.controls"
            :key="controlIndex"
            :value="value"
            :style="{ 'grid-column': control.grid.column, 'grid-row': control.grid.row }"
            :control="control"
            @input="$emit('input', $event)"
          >
            {{ control.text }}
          </component>
        </ControlContainer>
      </template>
    </masonry-wall>
    <ControlFooter class="pt-4" />
  </div>
</template>
