<script setup>
import * as sparkplug from './api.js'
import ControlPanel from './components/ControlPanel.vue'
import Header from './components/Header.vue'
import StatusDisplay from './components/StatusDisplay.vue'
import { ref } from 'vue'

let loading = ref(true);
let controlModels = ref({});
let lightsOut = ref(false);
let indicatorConfiguration = ref([]);

// Small viewport padding is determined by individual elements, to allow scrolling to screen edge.
const paddingSides = "px-6 md:px-8 lg:px-12 xl:px-20";
const paddingBottom = "pb-6 md:pb-8 lg:pb-12 xl:pb-20";

const debugSetMode = event => {
  console.log("Control input", event);

  Object.keys(event).forEach(modeID => {
    controlModels.value[modeID] = Number(event[modeID]);
  });
};

</script>

<template>
  <div v-if="loading">
    loading...
  </div>
  <div
    v-else
    class="min-h-screen bg-black text-foreground-200 md:bg-horizontal-split"
    :class="[ lightsOut ? 'lightsOut' : '' ]"
  >
    <div class="mx-auto flex min-h-screen flex-col md:flex-row lg:container">
      <!-- Status -->
      <div
        :class="paddingSides"
        class="flex-col md:sticky md:top-0 md:flex md:h-screen md:flex-1 md:self-start"
      >
        <div class="py-4">
          <Header :text="lightsOut ? '' : 'Sparkplug'">
            <template #beforeText>
              <mdicon
                name="sparkplug"
                class="text-foreground-400"
              />
            </template>
            <button
              class="mx-2 rounded-md bg-background-800 p-2 font-bold"
            >
              <mdicon name="??" />
            </button>
          </Header>
        </div>
        <StatusDisplay
          :control-models="controlModels"
          :indicator-configuration="indicatorConfiguration"
        />
        <div
          class="flex items-center justify-between pt-6"
          :class="[paddingBottom]"
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
        :class="paddingSides"
        class="flex flex-1 flex-col flex-col rounded-3xl rounded-b-none bg-background-800 md:flex md:flex-1"
      >
        <div class="py-4">
          <Header text="Controls" />
        </div>
        <ControlPanel
          class="flex flex-1 flex-col justify-between md:items-center md:justify-center"
          :class="[paddingBottom]"
          :value="controlModels"
          :control-config="sparkplug.controlsData"
          :padding-bottom="paddingBottom"
          @input="debugSetMode"
        />
      </div>
    </div>
  </div>
</template>

<script>
export default {
  async mounted() {
    try {
      await sparkplug.setup();
    }
    catch(e) {
      // Display error message in UI.
      return;
    }

    this.controlModels = {};
    sparkplug.lightingModes.forEach(mode => {
      this.controlModels[mode] = 0;
    });

    this.indicatorConfiguration = sparkplug.indicatorConfiguration;

    sparkplug.onGetMode(inputArguments =>
    {
      inputArguments.forEach(argument =>
      {
        const [modeIndex, modeState] = argument.split(":");
        const modeID = sparkplug.lightingModes[parseInt(modeIndex)];
        this.$set(this.controlModels, modeID, parseInt(modeState));
      });
    });

    // Get initial mode state.
    sparkplug.getModes();

    this.loading = false;
  }
}
</script>
