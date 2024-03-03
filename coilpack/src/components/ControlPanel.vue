<script setup>
import ControlContainer from "./ControlContainer.vue";
import DisplayControl from "./controls/DisplayControl.vue";
import IconControl from "./controls/IconControl.vue";
import Placeholder from "./controls/PlaceholderControl.vue";

defineProps({
  value: {
    type: Object,
    required: true,
  },
  controlConfig: {
    type: Object,
    required: true,
  },
});

defineEmits(["input"]);

const controlToComponent = {
  placeholder: Placeholder,
  button: IconControl,
  indicator: IconControl,
  display: DisplayControl,
};

// Automatic control panel grid sizing.
const autoCols = [
  "grid-cols-[repeat(2,calc((100vw-2*theme(spacing.6)-var(--gap-controls-x))/2))]",
  "sm:grid-cols-[repeat(2,200px)]",
];

const autoRows = [
  "auto-rows-[calc(((100vw-2_*_theme(spacing.6)_-_var(--gap-controls-x))/2_-_var(--gap-controls-y))/2)]",
  "sm:auto-rows-[calc((200px_-_var(--gap-controls-y))/2)]",
];
</script>

<template>
  <div>
    <div
      class="controlGrid grid w-full gap-x-controls-x gap-y-controls-y pb-10 xl:gap-10"
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
        :style="{
          'grid-area': `span ${item.height ?? 2} / span ${item.width ?? 1} / span ${item.height ?? 2} / span ${item.width ?? 1}`,
        }"
      >
        <component
          :is="controlToComponent[control.type]"
          v-for="(control, controlIndex) in item.controls"
          :key="controlIndex"
          :value="value"
          :style="{
            'grid-area': `${control.top ?? 'auto'} / ${control.left ?? 'auto'} / span ${control.height ?? 1} / span ${control.width ?? 1}`,
          }"
          :control="control"
          :type="control.type"
          @input="$emit('input', $event)"
        >
          {{ control.text }}
        </component>
        <template #header>
          {{ item.name }}
        </template>
      </ControlContainer>
    </div>
  </div>
</template>
