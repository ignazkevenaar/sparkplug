<script setup>
import ControlPanel from '../components/ControlPanel.vue'
import StatusDisplay from '../components/StatusDisplay.vue'
import { inject } from 'vue'

let sparkplug = inject('sparkplug');
let lightsOut = inject('lightsOut');
let controlModels = inject('controlModels');
let indicatorConfiguration = inject('indicatorConfiguration');

const debugSetMode = event => {
  console.log("Control input", event);

  Object.keys(event).forEach(modeID => {
    controlModels.value[modeID] = Number(event[modeID]);
  });
};
</script>

<template>
  <div
    class="min-h-screen bg-black text-foreground-200 md:bg-horizontal-split"
    :class="[ lightsOut ? 'lightsOut' : '' ]"
  >
    <div class="mx-auto flex min-h-screen flex-col md:flex-row lg:container">
      <!-- Status -->
      <div
        class="flex-col px-6 md:sticky md:top-0 md:flex md:h-screen md:flex-1 md:self-start md:px-8 lg:px-12 xl:px-20"
      >
        <!-- Header spacer -->
        <div class="flex h-20 items-center font-header text-lg font-semibold lg:h-32 2xl:text-xl" />

        <StatusDisplay
          :control-models="controlModels"
          :indicator-configuration="indicatorConfiguration"
        />
        <div
          class="flex items-center justify-between py-6 md:pb-8 lg:pb-12 xl:pb-20"
        >
          <button
            :class="lightsOut ? 'bg-foreground-50 text-background-700' : 'bg-background-700'"
            class="mx-2 shrink-0 rounded-full p-2 font-bold md:p-3"
            @click="lightsOut = !lightsOut"
          >
            <mdicon name="weather-night" />
          </button>
          <div class="text-center font-header text-foreground-300">
            <p class="text-xs leading-tight tracking-tighter">
              Volkswagen
            </p>
            <p>Golf <span class="text-foreground-300 text-opacity-50">Mk3</span></p>
          </div>
          <button
            class="mx-2 shrink-0 rounded-full bg-background-700 p-2 font-bold md:p-3"
          >
            <mdicon name="gesture-tap-hold" />
          </button>
        </div>
      </div>

      <!-- Controls -->
      <div
        class="flex flex-1 flex-col rounded-3xl rounded-b-none bg-background-800 px-6 md:flex md:flex-1 md:px-8 lg:px-12 xl:px-20"
      >
        <div class="flex h-20 items-center font-header text-lg font-semibold lg:h-32 2xl:text-xl">
          Controls
        </div>
        <ControlPanel
          class="flex flex-1 flex-col justify-between pb-6 md:items-center md:justify-center md:pb-8 lg:pb-12 xl:pb-20"
          :value="controlModels"
          :control-config="sparkplug.controlsData"
          @input="debugSetMode"
        />
      </div>
    </div>
  </div>
</template>
