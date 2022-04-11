<script setup>
import IndicatorLight from './IndicatorLight.vue';
import InlineSVG from './InlineSVG.vue'
import { ref } from 'vue';

const props = defineProps({
  controlModels: {
    type: Object,
    required: true
  },
  indicatorConfiguration: {
    type: Object,
    required: true
  }
});

const lightTest = ref(false);
const indicatorColumnCount = props.indicatorConfiguration.settings?.columns || 4;
</script>

<template>
  <div
    class="vfd flex flex-1 flex-col"
    :class="{ 'light-test': lightTest }"
  >
    <div
      id="indicators"
      class="mb-6 grid place-items-center gap-2"
    >
      <IndicatorLight
        v-for="(indicator, indicatorIndex) in indicatorConfiguration.indicators"
        :key="indicatorIndex"
        :value="controlModels"
        :indicator="indicator"
        class="min-h-0 w-10 md:w-16"
      />
    </div>
    <InlineSVG
      id="display"
      src="/display.svg"
      class="pointer-events-none relative grid min-h-[150px] flex-1 rotate-90 scale-[2] place-items-center fill-transparent stroke-[3px] md:aspect-auto md:rotate-0 md:scale-100 md:stroke-2"
    />

    <component :is="`style`">
      <template
        v-for="(modelValue, modelName) in controlModels"
        :key="modelName"
      >
        <template v-if="modelValue">
          .on-{{ modelName }} { --vfd-color: currentColor; }
        </template>
      </template>
    </component>
  </div>
</template>

<style lang="scss" scoped>
:deep(.mdi svg) {
  width: 100%;
  height: 100%;
}
</style>

<style lang="scss">
#indicators {
  grid-template-columns: repeat(v-bind(indicatorColumnCount), minmax(0, 1fr));
}

#display {
  svg {
    position: absolute;
    height: 100%;
    width: 100%;
    max-height: 600px;
  }
}

.vfd {
  --vfd-off: theme('colors.background.800'); //#331c1a;
  --vfd-color: var(--vfd-off);

  * {
    stroke: var(--vfd-color);
  }

  .fill,
  .fill svg {
    stroke-width: 0;
    fill: var(--vfd-color);
  }

  .red {
    @apply text-red-400;
  }
  .yellow {
    @apply text-yellow-400;
  }
  .green {
    @apply text-lime-400;
  }
  .blue {
    @apply text-blue-400;
  }

  .blink {
    animation: .66s blink infinite;

    &.fast {
      animation-duration: .33s;
    }
    &.slow {
      animation-duration: 2.4s;
    }

    @keyframes blink {
      50% {
        --vfd-color: var(--vfd-off);
      }
    }
  }

  .static {
    --vfd-color: currentColor !important;
  }

  &.light-test {
    * {
      --vfd-color: var(--vfd-on) !important;
    }

    .off {
      --vfd-color: var(--vfd-off) !important;
    }
  }
}
</style>
