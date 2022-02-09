<script setup>
import * as sparkplug from './api.js'
import { onMounted, ref } from 'vue'
import CarControls from './components/CarControls.vue'
import CarImage from './components/CarImage.vue'
import Container from './components/Container.vue'
import Header from './components/Header.vue'
import ModeToggler from './components/debug/ModeToggler.vue'

let loading = ref(true);
let controlModels = ref({});
let lightsOut = ref(false);

let body = ref(null);
let carImage = ref(null);

let finalHeight = ref(0);
let scrollTopPX = ref(0);

// Small viewport padding is determined by individual elements, to allow scrolling to screen edge.
const paddingSides = "px-6 md:px-8 lg:px-12 xl:px-20";
const paddingBottom = "pb-6 md:pb-8 xl:pb-20";

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
    ref="body"
    class="h-screen overflow-y-auto overflow-x-hidden bg-black text-foreground-200 md:flex"
    :class="[ lightsOut ? 'lightsOut' : '' ]"
    style="scroll-snap-type: y mandatory;"
  >
    <!-- Car image -->
    <Container
      id="carImage"
      ref="carImage"
      class="relative h-screen shrink-0 md:w-1/2 lg:w-[500px]"
      style="scroll-snap-align: start;"
      :padding="paddingSides"
    >
      <template #header>
        <Header text="Sparkplug">
          <template #beforeText>
            <mdicon name="flash" />
          </template>
        </Header>
      </template>
      <div
        class="relative h-full pt-6 md:pt-0"
        :class="[paddingSides, paddingBottom]"
      >
        <CarImage
          :final-height="finalHeight"
          :scroll-top="scrollTopPX"
          :control-models="controlModels"
          class="h-full"
          @toggle-lights-out="lightsOut = !lightsOut"
        />
      </div>
    </Container>

    <!-- Controls -->
    <Container
      class="bg-background-900"
      style="scroll-snap-align: start;"
      :padding="paddingSides"
    >
      <template #header>
        <Header text="Controls">
          <button
            class="mx-2 hidden rounded-md bg-background-700 p-2 px-4 font-bold md:block"
            :class="lightsOut ? 'bg-foreground-50 text-background-700' : ''"
            @click="lightsOut = !lightsOut"
          >
            Lights out
          </button>
        </Header>
      </template>
      <!-- <ModeToggler
        :value="controlModels"
        @input="debugSetMode"
      /> -->
      <CarControls
        :value="controlModels"
        :control-config="sparkplug.controlsData"
        :padding-sides="paddingSides"
        :padding-bottom="paddingBottom"
        @input="debugSetMode"
      />
    </Container>
  </div>
</template>

<script>
import { nextTick } from 'vue';

export default {
  async mounted() {
    await this.sparkplug.setup();

    this.controlModels = {};
    this.sparkplug.lightingModes.forEach(mode => {
      this.controlModels[mode] = 0;
    });

    this.sparkplug.onGetMode(inputArguments =>
    {
      inputArguments.forEach(argument =>
      {
        const [modeIndex, modeState] = argument.split(":");
        const modeID = this.sparkplug.lightingModes[parseInt(modeIndex)];
        this.$set(this.controlModels, modeID, parseInt(modeState));
      });
    });

    // Get initial mode state.
    this.sparkplug.getModes();

    this.loading = false;
    await nextTick();

    let ticking = false;

    this.body.addEventListener('scroll', () => {
      if (!ticking) {
        window.requestAnimationFrame(() => {
          const clientHeight = this.body.clientHeight;
          const scrollHeight = this.body.scrollHeight;
          this.scrollTopPX = this.body.scrollTop;

          document.documentElement.style.setProperty('--scroll',
            this.scrollTopPX / (scrollHeight - clientHeight)
          );

          ticking = false;
        });

        ticking = true;
      }
    });

    // Update final height.
    const getFinalHeight = ()=> {
      this.finalHeight = this.body.clientHeight -
        (this.body.scrollHeight - this.body.clientHeight);
    };

    const roControlGrid = new ResizeObserver(getFinalHeight);
    roControlGrid.observe(this.body);
  }
}
</script>
