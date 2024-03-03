<script setup>
import ControlPanel from "../components/ControlPanel.vue";
import { inject } from "vue";

const controlsConfig = inject("controlsConfig");
const controlModels = inject("controlModels");

const emit = defineEmits(["input"]);
</script>

<template>
  <div>
    <ControlPanel
      class="mx-auto flex flex-1 flex-col justify-between p-6 pb-2 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-6 lg:px-12 lg:pb-12 xl:px-20 xl:pb-10"
      :value="controlModels"
      :control-config="controlsConfig.status"
      @input="$emit('input', $event)"
    />
    <ControlPanel
      class="bg-controls-background mx-auto flex flex-1 flex-col justify-between p-6 lg:container md:flex md:flex-1 md:flex-row md:items-center md:justify-center md:px-8 md:pb-8 lg:px-12 lg:pb-12 xl:px-20 xl:pb-20"
      :value="controlModels"
      :control-config="controlsConfig.controls"
      @input="$emit('input', $event)"
    />
  </div>
</template>
