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

const roundClass = computed(() => props.control.round ? 'rounded-full' : 'rounded-lg md:rounded-2xl');

const colors = {
  default: {
    default: {
      background: [
        "bg-background-600",
        "active:bg-black",
        "active:text-foreground-500"
      ]
    },
    invert: {
      background: [
        "bg-foreground-50",,
        "text-background-700",
        "active:bg-foreground-200",
      ]
    },
    red: {
      background: [
        "bg-red-700",
        "active:bg-red-800",
        "text-white"
      ]
    },
    yellow: {
      background: [
        "bg-yellow-700",
        "active:bg-yellow-800",
        "text-white"
      ]
    },
    green: {
      background: [
        "bg-green-700",
        "active:bg-green-800",
        "text-white"
      ]
    },
    blue: {
      background: [
        "bg-blue-700",
        "active:bg-blue-800",
        "text-white"
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
  props.control.positions.slice(currentPositions.value[currentPositions.value.length - 1]?.index + 1)
    .find(position => position.type === 'hold')
);

const nextPosition = computed(() => currentPositions.value[currentPositions.value.length - 1]?.index + 1);
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
      currentPositions.value.length ? currentPositions.value.filter(position =>
        !holdingPosition.value ? position.type !== 'hold' : true).map(position =>
          [key, (position[key] || props.control[key])]
        ) : [[key, props.control[key] || ""]]
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
    @mousedown.prevent="mouseDown"
    @mouseup.prevent="mouseUp"
    @touchstart.prevent="mouseDown"
    @touchend.prevent="mouseUp"
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
