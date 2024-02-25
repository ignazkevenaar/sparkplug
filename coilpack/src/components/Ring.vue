<script setup>
defineProps({
  startAngle: {
    type: Number,
    default: 0,
  },
  percent: {
    type: Number,
    default: 50,
  },
  strokeWidth: {
    type: Number,
    default: 5,
  },
});

const circumference = 50 * 2 * Math.PI;
</script>

<template>
  <div>
    <svg
      class="h-full w-full overflow-visible"
      :style="{ transform: `rotate(${-90 + startAngle}deg)` }"
      :stroke-width="strokeWidth"
      fill="transparent"
    >
      <circle class="stroke-current opacity-10" r="50%" cx="50%" cy="50%" />
      <circle
        class="stroke-current"
        :stroke-dasharray="`${circumference}%`"
        :stroke-dashoffset="`${circumference - (percent / 100) * circumference}%`"
        stroke-linecap="round"
        r="50%"
        cx="50%"
        cy="50%"
      />
    </svg>
  </div>
</template>
