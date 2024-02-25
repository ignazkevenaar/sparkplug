<script setup>
import * as sparkplug from './api.js'
import { onMounted, provide, ref } from 'vue'
import AppHeader from './components/AppHeader.vue'
import AppRouter from './components/AppRouter.vue'
import ErrorMessage from './components/ErrorMessage.vue'
import HeaderButton from './components/HeaderButton.vue'
import LoadingIndicator from './components/LoadingIndicator.vue'

const loading = ref(true);
const error = ref(null);
const lightsOut = ref(false);
const currentRoute = ref('/');
const config = ref({});
const lightingModes = ref([]);
const controlModels = ref({});
const indicatorConfiguration = ref([]);

provide('sparkplug', sparkplug);
provide('lightsOut', lightsOut);
provide('lightingModes', lightingModes);
provide('controlModels', controlModels);
provide('indicatorConfiguration', indicatorConfiguration);

const navigateHome = () => { window.location.href = '#/' };
const scollToTop = () => { window.scrollTo(0, 0); }

onMounted(async () => {
  try {
    await sparkplug.setup();
  }
  catch(e) {
    // Display error message in UI.
    console.log(e);
    return;
  }

  config.value = sparkplug.config;
  lightingModes.value = sparkplug.lightingModes;
  controlModels.value = {};
  sparkplug.lightingModes.forEach(mode => {
    controlModels.value[mode] = 0;
  });

  if (config.value?.name)
  {
    document.title = `Sparkplug — ${config.value.name}`;
  }

  indicatorConfiguration.value = sparkplug.indicatorConfiguration;

  sparkplug.onGetMode(inputArguments =>
  {
    inputArguments.forEach(argument =>
    {
      const [modeIndex, modeState] = argument.split(":");
      const modeID = sparkplug.lightingModes[parseInt(modeIndex)];
      controlModels.value[modeID] = parseInt(modeState);
    });
  });

  // Get initial mode state.
  sparkplug.getModes();

  loading.value = false;
})

// Animation timers for controls.
const blinkNormal = ref(false);
setInterval(() => { blinkNormal.value = !blinkNormal.value; }, 300);
provide('blink-normal', blinkNormal);

const blinkFast = ref(false);
setInterval(() => { blinkFast.value = !blinkFast.value; }, 150);
provide('blink-fast', blinkFast);
</script>

<template>
  <div
    :class="[ lightsOut ? 'lightsOut' : '' ]"
    class="relative min-h-screen bg-background"
  >
    <AppHeader
      :show-back-button="currentRoute != '' && currentRoute != '/'"
      :subtitle="config.name"
      @on-back="navigateHome"
      @on-logo="scollToTop"
    >
      <template #left>
        <HeaderButton icon="weather-night" />
      </template>
      <template #right>
        <HeaderButton icon="power-standby" />
      </template>
    </AppHeader>
    <Transition mode="out-in">
      <div
        v-if="loading"
        class="absolute inset-0 grid place-items-center"
      >
        <LoadingIndicator />
      </div>
      <div
        v-else-if="error"
        class="absolute inset-0 grid place-items-center"
      >
        <ErrorMessage :error="error" />
      </div>
      <AppRouter
        v-else
        @route-changed="currentRoute = $event"
      />
    </Transition>
  </div>
</template>
