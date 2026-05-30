<script setup>
import { onBeforeUnmount, onMounted, ref, watchEffect } from "vue";
import SequencerPattern from "./BlinkerSequencer/SequencerPattern.vue";
import SequencerButton from "./BlinkerSequencer/SequencerButton.vue";
import SequencerDialog from "./BlinkerSequencer/SequencerDialog.vue";
const PATTERNLENGTH = 32;

const patterns = ref([]);

const index = ref(0);
const started = ref(true);
const intervalMS = ref(600);

let interval;

const increaseIndex = () => {
  index.value = (index.value + 1) % PATTERNLENGTH;
};

watchEffect(() => {
  if (interval) {
    clearInterval(interval);
    interval = undefined;
  }

  if (started.value) {
    interval = setInterval(increaseIndex, intervalMS.value / PATTERNLENGTH);
  }
});

const addPattern = () => {
  patterns.value.push({
    subdivision: 4,
    ticks: [
      ...Array.from(Array(PATTERNLENGTH / 2)).fill(true),
      ...Array.from(Array(PATTERNLENGTH / 2)).fill(false),
    ],
  });
};

onBeforeUnmount(() => {
  if (interval) clearInterval(interval);
});

onMounted(() => {
  addPattern();
});

const deletePattern = (patternIndex) => {
  patterns.value.splice(patternIndex, 1);
};

const exportDialog = ref(undefined);
const exportPatterns = () => {
  exportDialog.value?.open();
};
</script>

<template>
  <div class="container">
    <h4>Blinker Sequencer</h4>
    <div>
      <div class="grid">
        <SequencerPattern
          v-for="(pattern, patternIndex) in patterns"
          :key="patternIndex"
          v-model="patterns[patternIndex].ticks"
          v-model:subdivision="patterns[patternIndex].subdivision"
          :index="index"
          class="pattern"
          @delete="deletePattern(patternIndex)"
        />
      </div>

      <div class="toolbar">
        <SequencerButton @click="started = !started">
          <svg
            v-if="started"
            xmlns="http://www.w3.org/2000/svg"
            viewBox="0 0 24 24"
          >
            <path d="M18,18H6V6H18V18Z" />
          </svg>
          <svg v-else xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
            <path d="M8,5.14V19.14L19,12.14L8,5.14Z" />
          </svg>
          <span>{{ started ? "Stop" : "Start" }}</span>
        </SequencerButton>
        Period:
        <input type="number" v-model="intervalMS" />
        ms
        <div class="spacer" />
        <SequencerButton @click="exportPatterns">
          <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
            <title>export</title>
            <path
              d="M23,12L19,8V11H10V13H19V16M1,18V6C1,4.89 1.9,4 3,4H15A2,2 0 0,1 17,6V9H15V6H3V18H15V15H17V18A2,2 0 0,1 15,20H3A2,2 0 0,1 1,18Z"
            />
          </svg>
          Export
        </SequencerButton>
        <SequencerButton @click="addPattern">
          <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
            <title>plus-circle-outline</title>
            <path
              d="M12,20C7.59,20 4,16.41 4,12C4,7.59 7.59,4 12,4C16.41,4 20,7.59 20,12C20,16.41 16.41,20 12,20M12,2A10,10 0 0,0 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2M13,7H11V11H7V13H11V17H13V13H17V11H13V7Z"
            />
          </svg>
          Add pattern
        </SequencerButton>
      </div>
    </div>
    <SequencerDialog ref="exportDialog">
      <div class="mono">
        <template v-for="(pattern, patternIndex) in patterns">
          uint32_t pattern_{{ patternIndex }} = 0b{{
            pattern.ticks.map(Number).join("")
          }};<br />
        </template>
      </div>
    </SequencerDialog>
  </div>
</template>

<style lang="css" scoped>
.container {
  font-size: 0.8rem;
}

h4 {
  margin-top: 0;
  margin-bottom: 8px;
}

.container {
  color: oklch(92.2% 0.005 325.62);
  background: oklch(26.3% 0.024 320.12);
  padding: 20px;
  border-radius: 10px;
}

.grid {
  display: grid;
  grid-template-columns: min-content 1fr max-content;
  gap: 8px;

  .pattern {
    grid-column: span 3 / span 3;
  }
}

.toolbar {
  margin-top: 8px;
  display: flex;
  gap: 4px;
  align-items: center;

  .spacer {
    flex: 1;
  }
}

input {
  padding-inline: 8px;
  border-radius: 4px;
  background: oklch(26.3% 0.024 320.12);
  border: 1px solid oklch(43.5% 0.029 321.78);
  width: 72px;
}

:deep(button) {
  svg {
    flex: 0 0 18px;
    width: 18px;
    height: 18px;
    fill: currentColor;
  }
}

dialog {
  .mono {
    padding: 16px;
    border-radius: 8px;
    background-color: black;
    font-family: monospace;
  }
}
</style>
