<script>
import ControlView from "../views/ControlView.vue";
import InfoView from "../views/InfoView.vue";

const routes = {
  '/': ControlView,
  '/info': InfoView
}

export default {
  emits: ['route-changed'],
  data() {
    return {
      currentPath: window.location.hash
    }
  },
  computed: {
    currentView() {
      return routes[this.currentPath.slice(1) || '/'] || ControlView
    }
  },
  watch: {
    currentView: {
      handler () {
        this.$emit('route-changed', this.currentPath.slice(1));
      },
      immediate: true
    }
  },
  mounted() {
    window.addEventListener('hashchange', () => {
		  this.currentPath = window.location.hash
		})
  }
}
</script>

<template>
  <Transition mode="out-in">
    <component :is="currentView" />
  </Transition>
</template>
