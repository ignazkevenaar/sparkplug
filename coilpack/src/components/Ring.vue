<script setup>
defineProps({
  startAngle: {
    type: Number,
    default: 0
  },
  percent: {
    type: Number,
    default: 50
  },
  strokeWidth: {
    type: Number,
    default: 5
  }
})

const circumference = 50 * 2 * Math.PI;
</script>

<template>
  <div>
    <svg
      class="h-full w-full overflow-visible"
      :style="{ transform: `rotate(${ -90 + startAngle }deg)` }"
      :stroke-width="strokeWidth"
      fill="transparent"
    >
      <defs>
        <linearGradient
          id="linear"
          x1="0%"
          y1="0%"
          x2="100%"
          y2="0%"
        >
          <stop
            offset="0%"
            stop-color="#05a"
          />
          <stop
            offset="100%"
            stop-color="#0a5"
          />
        </linearGradient>
      </defs>
      <!-- <circle
        class="text-gray-300 stroke-current"
        r="50%"
        cx="50%"
        cy="50%"
      /> -->
      <circle
        class="stroke-current text-foreground-700"
        :stroke-dasharray="`${ circumference }%`"
        :stroke-dashoffset="`${ circumference - percent / 100 * circumference }%`"
        stroke-linecap="round"
        r="50%"
        cx="50%"
        cy="50%"
        stroke="url(#linear)"
      />
    </svg>
  </div>
</template>
