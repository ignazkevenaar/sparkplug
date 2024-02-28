<script setup>
import ControlPanel from "../components/ControlPanel.vue";
import StatusDisplay from "../components/controls/StatusControl.vue";
import { inject } from "vue";

let sparkplug = inject("sparkplug");
let lightsOut = inject("lightsOut");
let lightingModes = inject("lightingModes");
let controlModels = inject("controlModels");

const emit = defineEmits(["input"]);

const groupAndSetModeChanges = (event) => {
  console.log("Control input", event);

  const setModeStrings = [];
  const unsetModeStrings = [];

  Object.keys(event).forEach((modeID) => {
    const newValue = Number(event[modeID]);
    controlModels.value[modeID] = newValue;

    const modeIndex = lightingModes.value.indexOf(modeID);
    if (modeIndex > -1) {
      if (newValue === 1) setModeStrings.push(modeIndex);
      else if (newValue === 0) unsetModeStrings.push(modeIndex);
    }
  });

  if (setModeStrings.length) sparkplug.setMode(setModeStrings);
  if (unsetModeStrings.length) sparkplug.unsetMode(unsetModeStrings);
};
</script>

<template>
  <div>
    <ControlPanel
      class="mx-auto flex flex-1 flex-col justify-between p-6 pb-2 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-6 lg:px-12 lg:pb-12 xl:px-20 xl:pb-10"
      :value="controlModels"
      :control-config="sparkplug.controlsData.status"
      @input="groupAndSetModeChanges"
    />
    <ControlPanel
      class="bg-controls-background mx-auto flex flex-1 flex-col justify-between p-6 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-8 lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
      :value="controlModels"
      :control-config="sparkplug.controlsData.controls"
      @input="groupAndSetModeChanges"
    />
  </div>
</template>
