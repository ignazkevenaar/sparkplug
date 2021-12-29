<script setup>
import { ref, computed } from 'vue';
import InlineSVG from './InlineSVG.vue'

const props = defineProps({
  scrollTop: {
    type: Number,
    default: 0
  },
  finalHeight: {
    type: Number,
    default: 0
  },
  controlModels: {
    type: Object,
    required: true
  }
});

const emit = defineEmits(['toggle-lights-out'])

const hasScrolled = computed(() => props.scrollTop > 0);

const lightTest = ref(false);
</script>

<template>
  <div
    class="relative vfd"
    :class="{ 'light-test': lightTest }"
  >
    <!-- Side toolbars -->
    <div
      class="flex absolute bottom-0 justify-between w-full fade-out"
      :style="{ height: `calc(${ finalHeight }px - 3rem)` }"
      :class="{ hide: !hasScrolled }"
    >
      <div class="grid grow grid-rows-4 gap-px items-center ">
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
      </div>
      <div class="grid grow grid-rows-4 gap-px justify-items-end items-center">
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
        <div class="max-w-[3rem] h-full max-h-[3rem] bg-background-700 rounded-lg aspect-square" />
      </div>
    </div>

    <!-- Car image -->
    <InlineSVG
      src="/car.svg"
      class="grid overflow-hidden absolute bottom-0 place-items-center w-full fill-[none] stroke-2 lg:stroke-[1.5px] carImage"
    />

    <!-- Top toolbar -->
    <div class="sticky top-0">
      <!-- Header -->
      <div class="flex md:hidden justify-between items-center mb-6">
        <button
          class="w-12 h-12 bg-background-700 rounded-full fade-out"
          :class="{ hide: hasScrolled }"
        />
        <p class="mx-auto font-header text-lg font-bold tracking-tight">
          Sparkplug
        </p>
        <button
          class="w-12 h-12 bg-background-700 rounded-full fade-out"
          :class="{ hide: hasScrolled }"
        />
      </div>
      <!-- Indicator lights -->
      <div
        class="grid grid-cols-5 gap-6 fade-out"
        :class="{ hide: hasScrolled }"
      >
        <div class="relative aspect-square">
          <mdicon
            name="flash"
            class="absolute top-0 left-0 w-full h-full green on-BlinkL blink fill"
          />
        </div>
        <div class="bg-background-700 rounded-lg aspect-square" />
        <div class="bg-background-700 rounded-lg aspect-square" />
        <div class="bg-background-700 rounded-lg aspect-square" />
        <div class="bg-background-700 rounded-lg aspect-square" />
        <div class="bg-background-700 rounded-lg aspect-square" />
        <div class="col-start-5 bg-background-700 rounded-lg aspect-square" />
      </div>
    </div>

    <!-- Bottom toolbar -->
    <div
      class="absolute bottom-0 w-full text-center select-none fade-out"
      :class="{ hide: hasScrolled }"
    >
      <div class="flex justify-between">
        <button
          class="grid place-items-center w-12 h-12 bg-background-700 rounded-full"
          @mousedown="lightTest = true;"
          @mouseup="lightTest = false;"
        >
          LT
        </button>
        <div>
          <p class="pb-0 mx-auto font-bold">
            Volkswagen
          </p>
          <p class="mx-auto font-header text-lg font-bold tracking-tight">
            Golf <span class="text-foreground-500">mk3</span>
          </p>
        </div>
        <button
          class="grid place-items-center w-12 h-12 bg-background-700 rounded-full"
          @click="$emit('toggle-lights-out')"
        >
          LO
        </button>
      </div>
    </div>

    <component :is="`style`">
      <template
        v-for="(modelValue, modelName) in controlModels"
        :key="modelName"
      >
        <template v-if="modelValue">
          .on-{{ modelName }} { --vfd-color: var(--vfd-on); }
        </template>
        <template v-else>
          .on-{{ modelName }} { --vfd-color: var(--vfd-off) !important; }
        </template>
      </template>
    </component>
  </div>
</template>

<style lang="scss">
.fade-out {
  transition: opacity .5s .5s;

  &.hide {
    transition: opacity .25s 0s;
    opacity: 0;
  }
}

.carImage {
  animation: changeHeight 1s infinite;
  animation-play-state: paused;
  animation-delay: calc(var(--scroll) * -1s);
  animation-iteration-count: 1;
  animation-fill-mode: both;
  animation-timing-function: linear;

  @keyframes changeHeight {
    from {
      height: calc(100%);
    }

    to {
      height: calc(v-bind(finalHeight) * 1px - 3rem);
    }
  }

  svg {
    @apply h-full;

    transform-origin: center;
    animation: vertToHor 1s infinite;

    /* Pause the animation */
    animation-play-state: paused;
    /* Bind the animation to scroll */
    animation-delay: calc(var(--scroll) * -1s);
    /* These last 2 properites clean up overshoot weirdness */
    animation-iteration-count: 1;
    animation-fill-mode: both;
    animation-timing-function: linear;

    @keyframes vertToHor {
      from {
        transform: scale(.65) translate(0, 10%);
      }

      to {
        transform: scale(.75) rotate(-90deg) translate(0);
        height: 65vw;
      }
    }
  }
}

.vfd {
  --vfd-off: #331c1a;
  --vfd-on: theme('colors.foreground.200');
  --vfd-color: var(--vfd-off);

  * {
    stroke: var(--vfd-color);
  }

  .fill,
  .fill svg {
    stroke-width: 0;
    fill: var(--vfd-color);
  }

  .on {
    --vfd-color: var(--vfd-on)
  }

  .red {
    // @apply text-red-400;
    color: #f47e00;
    --vfd-on: currentColor;
  }
  .green {
    @apply text-lime-400;
    --vfd-on: currentColor;
  }
  .blue {
    @apply text-blue-400;
    --vfd-on: currentColor;
  }

  .blink {
    animation: .66s blink infinite;

    &.fast {
      animation-duration: .33s;
    }
    &.slow {
      animation-duration: 2.4s;
    }

    // Leverage the fact that CSS variables can't animate smoothly.
    @keyframes blink {
      50% {
        --vfd-color: var(--vfd-off);
      }

      to {
        --vfd-color: var(--vfd-on);
      }
    }
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
