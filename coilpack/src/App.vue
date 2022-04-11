<script setup>
import * as sparkplug from './api.js'
import { provide, ref } from 'vue'
import AppHeader from './components/AppHeader.vue'
import AppRouter from './components/AppRouter.vue'
import ErrorMessage from './components/ErrorMessage.vue'
import LoadingIndicator from './components/LoadingIndicator.vue'

let loading = ref(true);
let error = ref(null);
let lightsOut = ref(false);
let currentRoute = ref('/');
let controlModels = ref({});
let indicatorConfiguration = ref([]);

provide('sparkplug', sparkplug);
provide('lightsOut', lightsOut);
provide('controlModels', controlModels);
provide('indicatorConfiguration', indicatorConfiguration);

const navigateHome = () => { window.location.href = '#/' };
const scollToTop = () => { window.scrollTo(0, 0); }
</script>

<template>
  <AppHeader
    :show-back-button="currentRoute != '' && currentRoute != '/'"
    @on-back="navigateHome"
    @on-logo="scollToTop"
  />
  <Transition mode="out-in">
    <div
      v-if="loading"
      class="absolute grid h-screen w-screen place-items-center"
    >
      <LoadingIndicator />
    </div>
    <div
      v-else-if="error"
      class="absolute grid h-screen w-screen place-items-center"
    >
      <ErrorMessage :error="error" />
    </div>
    <div v-else>
      <AppRouter
        @route-changed="currentRoute = $event"
      />
    </div>
  </Transition>
</template>

<script>
export default {
  async mounted() {
    try {
      await sparkplug.setup();
    }
    catch(e) {
      // Display error message in UI.
      console.log(e);
      return;
    }

    // this.error = {
    //   message: "This is a test error!"
    // };

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
