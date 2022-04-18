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

const roundClass = computed(() => props.control.round ?
  'rounded-full' : 'rounded-lg md:rounded-2xl @squircle:squircle-xl @squircle:!rounded-none');

const colors = {
  default: {
    default: {
      background: [
        "bg-background-700",
        "active:bg-background-800",
        "lo:text-lightsOut-300",
        "ring-background-600/50"
      ]
    },
    red: {
      background: [
        "bg-red-900/25",
        "text-red-500",
        "ring-red-800/50",
      ]
    },
    yellow: {
      background: [
        "bg-yellow-700/25",
        "text-yellow-300",
        "ring-yellow-600/50",
        "lo:text-lightsOut-300",
        "lo:ring-background-600/50"
      ]
    },
    green: {
      background: [
        "bg-lime-700/25",
        "text-lime-300",
        "ring-green-600/50",
        "lo:text-lightsOut-300",
        "lo:ring-background-600/50"
      ]
    },
    blue: {
      background: [
        "bg-blue-700/25",
        "text-blue-400",
        "ring-blue-600/50",
        "lo:text-lightsOut-300",
        "lo:ring-background-600/50"
      ]
    }
  },
  toggled: {
    default: {
      background: [
        "bg-foreground-50",
        "text-background-700",
        "active:bg-foreground-100",
        "ring-foreground-50",
        "lo:text-lightsOut-100",
        "lo:bg-lightsOut-900",
        "lo:ring-lightsOut-500",
      ]
    },
    red: {
      background: [
        "bg-red-600",
        "active:bg-red-700",
        "text-black",
        "ring-red-600"
      ]
    },
    yellow: {
      background: [
        "bg-yellow-400",
        "active:bg-yellow-500",
        "text-black",
        "ring-yellow-400"
      ]
    },
    green: {
      background: [
        "bg-lime-400",
        "active:bg-lime-500",
        "text-black",
        "ring-lime-400"
      ]
    },
    blue: {
      background: [
        "bg-blue-400",
        "active:bg-blue-500",
        "text-black",
        "ring-blue-400"
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
  'icon',
  'style'
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

const colorClass = computed(() => colors[cascadedProps.value.style || 'default'][cascadedProps.value.color || 'default'].background);

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
    class="relative z-0 flex cursor-pointer select-none flex-col items-center justify-center bg-gradient-to-br p-2 text-center text-sm font-semibold ring-2 ring-inset"
    :class="[roundClass, colorClass]"
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
    <div
      v-if="holdPosition || holdingPosition"
      class="absolute bottom-1 h-1 w-5 rounded-full bg-current opacity-75"
    />
  </button>
</template>
