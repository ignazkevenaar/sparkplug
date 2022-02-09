<script setup>
import { computed, ref } from 'vue';

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

const roundClass = computed(() => props.round ? 'rounded-full' : 'rounded-2xl');

const colors = {
  default: {
    default: {
      background: [
        "from-background-700",
        "to-background-800",
        "active:from-background-800",
        "active:to-background-900",
        "active:text-foreground-500"
      ]
    },
    red: {
      background: [
        "from-red-700",
        "to-red-800",
        "active:from-red-800",
        "active:to-red-900",
        "active:text-white",
        "text-white"
      ]
    },
    green: {
      background: [
        "from-green-700",
        "to-green-800",
        "active:from-green-800",
        "active:to-green-900",
        "active:text-white",
        "text-white"
      ]
    },
    blue: {
      background: [
        "from-blue-700",
        "to-blue-800",
        "active:from-blue-800",
        "active:to-blue-900",
        "active:text-foreground-500"
      ]
    }
  }
};

const currentPositions = computed(() =>
  props.control.positions.flatMap((position, positionIndex) => {
      const allModesApply = Object.keys(position.modes).every(mode =>
        props.value[mode] === Number(position.modes[mode])
      );

      return allModesApply ? [{...position, index: positionIndex}] : [];
    }
));

// Finds 'hold' position that comes later than the highest current position, if any.
const holdPosition = computed(() =>
  props.control.positions.slice(currentPositions.value[currentPositions.value.length - 1].index + 1)
    .find(position => position.type === 'hold')
);

const nextPosition = computed(() => currentPositions.value[currentPositions.value.length - 1].index + 1);
const nonHoldPosition = computed(() =>
  [
    ...props.control.positions.slice(nextPosition.value),
    ...props.control.positions.slice(0, nextPosition.value)
  ].find(position => position.type !== 'hold')
);

const cascadableProperties = [
  'color',
  'icon'
];

// Cascade properties from props, active positions.
// Conditionally filters hold positions when not holding.
// Filters cascaded null properties.
const cascadedProps = computed(() =>
  Object.fromEntries(
    cascadableProperties.flatMap(key =>
      currentPositions.value.filter(position =>
        !holdingPosition.value ? position.type !== 'hold' : true).map(position =>
          [key, (position[key] || props.control[key])]
        )
    ).filter(([key, value]) => !!value)
  )
);

const swapSetUnset = original => {
  var modified = { ...original };
  Object.keys(modified).forEach(key => {
    modified[key] = !modified[key];
  });
  return modified;
};

const colorClass = computed(() => colors.default[cascadedProps.value.color || 'default'].background);

const absorbEvent_ = event => {
  var e = event || window.event;
  e.preventDefault && e.preventDefault();
  e.stopPropagation && e.stopPropagation();
  e.cancelBubble = true;
  e.returnValue = false;
  return false;
}

let holding = ref(false);
let holdingPosition = ref(false);

const mouseDown = () => {
  holdTimeout = setTimeout(onHold, 150);
};

const mouseUp = event => {
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
    class="relative z-0 flex cursor-pointer select-none flex-col items-center justify-center bg-gradient-to-br p-2 text-center text-sm font-semibold"
    :class="[roundClass, colorClass]"
    @mousedown.stop.prevent="mouseDown"
    @mouseup.stop.prevent="mouseUp"
    @touchstart="mouseDown"
    @touchend="mouseUp"
  >
    <mdicon
      v-if="cascadedProps.icon"
      :name="cascadedProps.icon"
      size="48"
    />
    <slot />
    <div
      v-if="holdPosition || holdingPosition"
      class="absolute bottom-1 w-full justify-self-end text-3xl md:bottom-2"
    >
      ...
    </div>
  </button>
</template>
