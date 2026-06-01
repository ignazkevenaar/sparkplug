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
    class="text-red-highlight drop-shadow-red-highlight/50 flex flex-col items-center gap-3 font-mono font-bold drop-shadow-[0_0_15px]"
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
