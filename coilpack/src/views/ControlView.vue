<script setup>
import { defineEmits, inject } from 'vue'
import ControlPanel from '../components/ControlPanel.vue'
import StatusDisplay from '../components/StatusDisplay.vue'

let sparkplug = inject('sparkplug');
let lightsOut = inject('lightsOut');
let lightingModes = inject('lightingModes');
let controlModels = inject('controlModels');

const emit = defineEmits(['input'])

const debugSetMode = event => {
  console.log("Control input", event);

  const setModeStrings = [];
  const unsetModeStrings = [];

  Object.keys(event).forEach(modeID => {
    const newValue = Number(event[modeID]);
    controlModels.value[modeID] = newValue

    const modeIndex = lightingModes.value.indexOf(modeID);
    if (modeIndex > -1)
    {
      if (newValue === 1) setModeStrings.push(modeIndex);
      else if (newValue === 0) unsetModeStrings.push(modeIndex);
    }
  });

  if (setModeStrings.length) sparkplug.setMode(setModeStrings);
  if (unsetModeStrings.length) sparkplug.unsetMode(unsetModeStrings);
};
</script>

<template>
  <ControlPanel
    class="mx-auto flex flex-1 flex-col justify-between p-6 md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-8 md:pt-0 lg:container lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
    :value="controlModels"
    :control-config="sparkplug.controlsData"
    @input="debugSetMode"
  />
</template>
