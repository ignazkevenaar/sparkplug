<template>
  <div class="surround relative rounded-full p-[8%]">
    <div class="absolute top-0 left-0 h-full w-full rounded-full shadow" />
    <div class="gap relative h-full w-full rounded-full p-[12.5%]">
      <div class="absolute top-0 left-0 h-full w-full rounded-full shadow">
        <svg
          version="1.1"
          xmlns="http://www.w3.org/2000/svg"
          class="absolute top-[.5%] left-0 h-full w-full overflow-hidden rounded-full opacity-20"
        >
          <circle
            class="ridges stroke-current text-white"
            cx="50%"
            cy="50%"
            r="50%"
          />
        </svg>
        <svg
          version="1.1"
          xmlns="http://www.w3.org/2000/svg"
          class="absolute top-0 left-0 h-full w-full overflow-hidden rounded-full opacity-20"
        >
          <circle
            class="ridges stroke-current text-black"
            cx="50%"
            cy="50%"
            r="50%"
          />
        </svg>
      </div>
      <div class="front relative h-full w-full rounded-full">
        <div class="absolute h-full w-full rounded-full shadow">
          <div class="indent relative top-2 mx-auto h-[20%] w-1 rounded-md bg-background-600/10" />
        </div>
      </div>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.shadow {
  mix-blend-mode: overlay;
}

.surround .shadow {
    box-shadow: inset 0 10px 15px rgba(black, .75),
      0 2px 2px rgba(white, .20);
  }

.gap {
  box-shadow: 0 0 0 4px black;

  .shadow {
    box-shadow: 0 10px 15px black,
      inset 0 5px 10px rgba(black, .5),
      0 20px 10px rgba(white, .5),
      inset 0 2px 0 rgba(white, .5);
  }

  .ridges {
    fill: none;
    stroke-width: 26%;
    stroke-dasharray: 1%;
  }
}

.front .shadow {
    box-shadow: inset 0 3px 1px rgba(white, .25),
      inset 0 -3px 2px rgba(black, .5),
      0 -10px 10px rgba(white, .5),
      0 -5px 15px rgba(black, .75),
      0 15px 20px rgba(black, .75),
      0 20px 10px rgba(black, .25);
  }

.indent {
  box-shadow: inset 1px 2px 2px rgba(black, .5),
    0 1px 1px rgba(white, .75);

  mix-blend-mode: overlay;
  opacity: .75;
}
</style>
