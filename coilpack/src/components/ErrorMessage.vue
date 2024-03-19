<script setup lang="ts">
interface IProps {
  error: Error
  title?: string
}

const props = withDefaults(defineProps<IProps>(), {
  title: 'Error'
})

console.log(props.error)
</script>

<template>
  <div
    class="flex flex-col items-center gap-3 font-mono font-bold text-red-500 drop-shadow-[0_0_25px_rgba(255,0,0,0.5)]"
  >
    <mdicon name="sparkplug-sad" size="48" class="ml-2" />
    <div v-if="title?.length" class="bg-current px-1">
      <span class="uppercase text-black">{{ title }}</span>
    </div>
    <div class="text-center [overflow-wrap:anywhere]">
      {{ error.message }}
    </div>
  </div>
</template>
