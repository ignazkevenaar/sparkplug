<script setup>
import { computed, onMounted, ref, watch } from "vue";
import InlineSvg from "vue-inline-svg";
import colors from "../styles/displayColors";

const config = import.meta.env.VITE_CONFIG || "default";

const props = defineProps({
  value: {
    type: Object,
    required: true,
  },
  control: {
    type: Object,
    required: true,
  },
});

const displayElement = ref(null);
const originalElementClassLists = ref([]);

const SVGLoaded = (event) => {
  displayElement.value = event;

  props.control?.segments.forEach((segment) => {
    const segmentElements = event.querySelectorAll(segment.selector);

    const originalClasses = [];
    for (let i = 0; i < segmentElements.length; i++) {
      originalClasses.push(segmentElements[i].getAttribute("class"));
    }

    originalElementClassLists.value.push(originalClasses);
  });

  appyIndicatorClasses(cascadedProps.value);
};

const currentStatesPerSegment = computed(() =>
  props.control.segments.map((segment) => {
    if (!segment.states) return [];
    return segment.states.flatMap((position, positionIndex) => {
      const allModesApply = Object.keys(position.modes).every(
        (mode) => props.value[mode] === Number(position.modes[mode]),
      );
      return allModesApply ? [{ ...position, index: positionIndex }] : [];
    });
  }),
);

const anyModeApplies = computed(() =>
  currentStatesPerSegment.value.map((segment) => !!segment.length),
);

// Cascade magic proppers.
const cascadableProperties = ["color", "style", "onState"];

const cascadeProps = (segment, activeSegmentStates) =>
  Object.fromEntries(
    cascadableProperties
      .flatMap((key) =>
        activeSegmentStates.length
          ? activeSegmentStates.map((position) => [
              key,
              position[key] || segment[key],
            ])
          : [[key, segment[key] || ""]],
      )
      .filter(([key, value]) => !!value),
  );

const cascadedProps = computed(() =>
  currentStatesPerSegment.value.map((states, segmentIndex) =>
    cascadeProps(props.control.segments[segmentIndex], states),
  ),
);

const colorClassPerSegment = (props, anyMode) => {
  const color = props.color || "default";
  const style = props.style || "stroke";
  const onState = props.onState || anyMode ? "on" : "off"; //Replace 'off' with sensible state.

  return [...colors.common[style], ...(colors[color][onState] || [])];
};

const appyIndicatorClasses = (newSegmentsProps) => {
  newSegmentsProps.forEach((segmentProps, index) => {
    const segment = props.control.segments[index];
    const activeSegmentElements = displayElement.value.querySelectorAll(
      segment.selector,
    );

    for (let i = 0; i < activeSegmentElements.length; i++) {
      const classes = colorClassPerSegment(
        segmentProps,
        anyModeApplies.value[index],
      );
      activeSegmentElements[i].setAttribute(
        "class",
        originalElementClassLists.value[index][i] + " " + classes.join(" "),
      );
    }
  });
};

watch(cascadedProps, (newSegmentsProps) => {
  appyIndicatorClasses(newSegmentsProps);
});
</script>

<template>
  <div class="flex flex-1 flex-col">
    <inline-svg
      :src="`/configs/${config}/display.svg`"
      class="pointer-events-none relative grid flex-1 place-items-center fill-transparent stroke-2"
      @loaded="SVGLoaded($event)"
    />
  </div>
</template>

<style lang="scss" scoped>
:deep(.mdi svg) {
  width: 100%;
  height: 100%;
}
</style>

<style lang="scss">
#display {
  svg {
    position: absolute;
    height: 100%;
    width: 100%;
    max-height: 600px;
  }
}
</style>
