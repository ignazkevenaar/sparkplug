<script setup lang="ts">
import { type Component, computed, onMounted, ref, watch } from 'vue'
import ControlView from '../views/ControlView.vue'
import InfoView from '../views/InfoView.vue'

const routes: { [path: string]: Component } = {
  '/': ControlView,
  '/info': InfoView
}

const currentPath = ref(window.location.hash)

const emit = defineEmits<{
  routeChanged: [path: string]
}>()

const currentView = computed(() => {
  return routes[currentPath.value.slice(1) || '/'] || ControlView
})

watch(
  currentView,
  async () => {
    emit('routeChanged', currentPath.value.slice(1))
  },
  { immediate: true }
)

onMounted(() => {
  window.addEventListener('hashchange', () => {
    currentPath.value = window.location.hash
  })
})
</script>

<template>
  <Transition mode="out-in">
    <component :is="currentView" v-bind="$attrs" />
  </Transition>
</template>
