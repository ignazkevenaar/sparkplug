<script setup>
import { computed, inject, ref } from 'vue';
import colors from '../styles/buttonColors';

const props = defineProps({
  value: {
    type: Object,
    required: true
  },
  control: {
    type: Object,
    required: true
  }
});

const emit = defineEmits(['input']);

// Animation timers
const blinkNormal = inject('blink-normal');
const blinkFast = inject('blink-fast');

const roundClass = computed(() => props.control.round ?
  'rounded-full' : 'rounded-lg md:rounded-2xl @squircle:squircle-xl @squircle:!rounded-none');

const currentPositions = computed(() =>
  props.control.positions.flatMap((position, positionIndex) => {
      const allModesApply = Object.keys(position.modes).every(mode =>
        props.value[mode] === Number(position.modes[mode])
      );

      return allModesApply ? [{...position, index: positionIndex}] : [];
    }
));
const nextPositionIndex = computed(() => currentPositions.value[currentPositions.value.length - 1]?.index + 1);

// Finds 'hold' position that comes later than the highest current position, if any.
const holdPosition = computed(() =>
  props.control.positions.slice(nextPositionIndex.value).find(
    position => position.type === 'hold'
  )
);

// The pair of slices wraps around the array.
// [3,4,0,1,2]
//      ^
const nonHoldPosition = computed(() =>
  [
    ...props.control.positions.slice(nextPositionIndex.value),
    ...props.control.positions.slice(0, nextPositionIndex.value)
  ].find(position => position.type !== 'hold')
);

const cascadableProperties = [
  'backgroundColor',
  'backgroundStyle',
  'foregroundColor',
  'foregroundStyle',
  'animation',
  'icon',
  'label',
];

// Cascade properties from props, active positions.
// Conditionally filters hold positions when not holding.
// Filters cascaded null properties.
const cascadedProps = computed(() =>
  Object.fromEntries(
    cascadableProperties.flatMap(key =>
    {
      const v = currentPositions.value
        .filter(position => !holdingPosition.value ? position.type !== 'hold' : true)
        .filter(position => !(blinkNormal.value && position.animation === 'blinking'))
        .map(position => [key, (position[key] || props.control[key])]);

      return v.length ? v : [[key, props.control[key] || ""]]
    }).filter(([key, value]) => !!value)
  )
);

const swapSetUnset = original => {
  var modified = { ...original };
  Object.keys(modified).forEach(key => {
    modified[key] = !modified[key];
  });
  return modified;
};

const colorClasses = computed(() => {
  const backgroundColor = cascadedProps.value.backgroundColor || 'default';
  const foregroundColor = cascadedProps.value.foregroundColor || 'default';
  const backgroundStyle = cascadedProps.value.backgroundStyle || 'default';
  const foregroundStyle = cascadedProps.value.foregroundStyle || 'default';

  return [
    ...colors.common.background[backgroundStyle],
    ...colors.common.foreground[foregroundStyle],
    ...colors[backgroundColor].background[backgroundStyle] || [],
    ...colors[foregroundColor].foreground[foregroundStyle] || []
  ];
});

let buttonDown = ref(false);
let holding = ref(false);
let holdingPosition = ref(false);

const mouseDown = () => {
  if (props.control.readOnly) return;
  holdTimeout = setTimeout(onHold, 150);
  buttonDown.value = true;
};

const mouseUp = event => {
  if (props.control.readOnly) return;
  if (buttonDown.value) buttonDown.value = false;
  else return;

  clearTimeout(holdTimeout);

  if (holding.value)
  {
    if (holdingPosition.value) emit('input', swapSetUnset(holdingPosition.value.modes));

    holding.value = false;
    holdingPosition.value = false;

    window.removeEventListener("mouseup", mouseUp);
    return;
  }

  // Send modes of next (or first) non-drag-mode.
  emit('input', nonHoldPosition.value.modes);
};

let holdTimeout;

const onHold = event => {
  // So mouse up events temporarily work outside of button bounds.
  window.addEventListener("mouseup", mouseUp);
  holding.value = true

  if (holdPosition.value)
  {
    holdingPosition.value = holdPosition.value;
    emit('input', holdPosition.value.modes);
  }
};
</script>

<template>
  <button
    class="relative z-0 flex select-none flex-col items-center justify-center bg-gradient-to-br p-2 text-center text-xs md:text-sm md:font-semibold ring-inset enabled:cursor-pointer"
    :class="[roundClass, colorClasses]"
    :disabled="control.readOnly"
    @mousedown.prevent="mouseDown"
    @mouseup.prevent="mouseUp"
    @touchstart.prevent="mouseDown"
    @touchend.prevent="mouseUp"
  >
    <mdicon
      v-if="cascadedProps.icon"
      :name="cascadedProps.icon"
      size="36"
    />
    <slot />
    {{ cascadedProps.label }}
    <div
      v-if="holdPosition || holdingPosition"
      class="absolute bottom-1 h-1 w-5 rounded-full bg-current opacity-75"
    />
  </button>
</template>
