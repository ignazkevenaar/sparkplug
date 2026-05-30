<script setup>
import { ref, onMounted, toRaw } from "vue";
import SequencerButton from "./SequencerButton.vue";

const model = defineModel({ type: Array });
const subdivision = defineModel("subdivision", { type: Number });

const props = defineProps({
  index: Number,
});

const emit = defineEmits(["delete"]);

const propagateBlocks = (valueToCopy, index) => {
  const clonedValue = structuredClone(toRaw(model.value));
  const blockCount = clonedValue.length / subdivision.value;
  const blockSize = clonedValue.length / blockCount;

  for (let block = 0; block < blockCount; block++) {
    const start = block * blockSize;
    if (
      valueToCopy !== undefined &&
      start >= index &&
      start < index + blockSize
    ) {
      clonedValue[start] = valueToCopy;
    }
    const value = clonedValue[start];

    // Copy first value of the block into the rest
    for (let i = start + 1; i < start + blockSize; i++) {
      clonedValue[i] = value;
    }
  }

  return clonedValue;
};

const toggleBlock = (stepIndex) => {
  model.value = propagateBlocks(!model.value[stepIndex], stepIndex);
};

const increaseSubdivide = () => {
  let buffer = subdivision.value;
  buffer *= 2;
  if (buffer > 8) buffer = 8;
  subdivision.value = buffer;
  model.value = propagateBlocks();
};

const decreaseSubdivide = () => {
  let buffer = subdivision.value;
  buffer /= 2;
  if (buffer < 1) buffer = 1;
  subdivision.value = buffer;
};

const cursorInRange = (stepIndex) =>
  props.index >= stepIndex && props.index < stepIndex + subdivision.value;

const isPinstriped = (stepIndex) => {
  const quarter = model.value.length / 4;

  return (
    // 2nd quarter
    (stepIndex >= quarter && stepIndex < quarter * 2) ||
    // 4th quarter
    (stepIndex >= quarter * 3 && stepIndex < model.value.length)
  );
};
</script>

<template>
  <div class="track">
    <div class="block indicator" :class="{ on: model[index] }"></div>
    <div class="pattern">
      <div class="blocks">
        <template v-for="(step, stepIndex) in model?.length" :key="step">
          <div
            v-if="stepIndex % subdivision === 0"
            class="block"
            :class="{
              pinstriped: isPinstriped(stepIndex),
              on: model[stepIndex],
            }"
            :style="{
              'grid-column': `span ${subdivision} / span ${subdivision}`,
            }"
            @click="toggleBlock(stepIndex)"
          >
            <div class="light" :class="{ on: cursorInRange(stepIndex) }"></div>
          </div>
        </template>
      </div>
    </div>
    <div class="toolbar">
      <SequencerButton @click="decreaseSubdivide">−</SequencerButton>
      <span class="timeScale">1/{{ subdivision }}</span>
      <SequencerButton @click="increaseSubdivide">+</SequencerButton>
      <SequencerButton @click="emit('delete')"
        ><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
          <title>Delete</title>
          <path
            d="M12,20C7.59,20 4,16.41 4,12C4,7.59 7.59,4 12,4C16.41,4 20,7.59 20,12C20,16.41 16.41,20 12,20M12,2A10,10 0 0,0 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2M7,13H17V11H7"
          /></svg
      ></SequencerButton>
    </div>
  </div>
</template>

<style lang="css" scoped>
.track {
  display: grid;
  grid-template-columns: subgrid;
  height: 100%;

  .blocks {
    height: 100%;
    display: grid;
    grid-template-columns: repeat(32, 1fr);
    gap: 2px;
  }

  .block {
    width: 100%;
    height: 100%;
    border: 1px solid oklch(43.5% 0.029 321.78);
    border-radius: 5px;
    user-select: none;
    cursor: pointer;
    background: oklch(36.4% 0.029 323.89);
    box-shadow: 0px 1px 3px rgba(0, 0, 0, 0.25);
    display: grid;
    padding-block: 4px;
    padding-inline: 4px;
    place-items: start center;

    .light {
      bottom: 4px;
      height: 2px;
      width: 100%;
      border-radius: 10px;
      background: rgba(0, 0, 0, 0.45);

      &.on {
        background: white;
      }
    }

    &.pinstriped {
      background: oklch(37.8% 0.015 216);
      border-color: oklch(45% 0.017 213.2);
    }

    &.on {
      background: oklch(51.1% 0.262 276.966);
      border-color: oklch(58.5% 0.233 277.117);
    }

    &.pinstriped.on {
      background: oklch(54.6% 0.245 262.881);
      border-color: oklch(62.3% 0.214 259.815);
    }

    &.selected {
      border-color: white;
    }

    &.indicator {
      width: 10px;
      border-radius: 4px;
      background-color: black;
      border-color: black;

      &.on {
        background: oklch(72.3% 0.219 149.579);
        border-color: oklch(79.2% 0.209 151.711);
      }
    }
  }
}

.toolbar {
  display: grid;
  grid-template-columns: repeat(3, 1fr) min-content;
  place-items: center;

  > *:last-child {
    margin-left: 8px;
  }

  button {
    height: 100%;
  }

  .timeScale {
    color: oklch(71.1% 0.019 323.02);
    font-size: 0.8em;
  }
}
</style>
