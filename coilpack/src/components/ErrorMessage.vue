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
    class="flex flex-col items-center gap-3 font-mono font-bold text-red-300 drop-shadow-[0_0_15px] drop-shadow-red-300/50"
  >
    <mdicon name="sparkplug-sad" size="48" class="ml-2" />
    <div v-if="title?.length" class="bg-current px-1">
      <span class="text-black uppercase">{{ title }}</span>
    </div>
    <div class="text-center wrap-anywhere">
      {{ error.message }}
    </div>
  </div>
</template>
