<script setup>
import InlineSVG from './InlineSVG.vue'
import { ref } from 'vue';

const props = defineProps({
  controlModels: {
    type: Object,
    required: true
  }
});

const lightTest = ref(false);
</script>

<template>
    <div
    class="vfd flex flex-1 flex-col"
      :class="{ 'light-test': lightTest }"
    >
      <div class="flex h-full justify-center gap-8 md:gap-12">
        <div class="flex flex-col justify-evenly">
          <mdicon
            name="arrow-left-bold-outline"
            class="green on-BlinkL blink fill min-h-0 w-10 md:w-16"
          />
          <mdicon
            name="car-light-fog"
            class="yellow on-BlinkL blink fill min-h-0 w-10 md:w-16"
          />
          <mdicon
            name="car-light-dimmed"
            class="green on-BlinkL blink fill min-h-0 w-10 md:w-16"
          />
          <mdicon
            name="car-parking-lights"
            class="green on-BlinkL blink fill min-h-0 w-10 md:w-16"
          />
        </div>
        <InlineSVG
          id="car"
          src="/car.svg"
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

<style lang="scss">
#car {
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

.mdi svg {
  width: 100%;
  height: 100%;
}
</style>
