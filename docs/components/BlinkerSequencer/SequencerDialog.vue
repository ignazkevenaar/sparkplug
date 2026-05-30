<script setup>
import { ref } from "vue";
import SequencerButton from "./SequencerButton.vue";

const dialog = ref(undefined);
const open = () => {
  dialog.value?.showModal();
};

const close = () => {
  dialog.value?.close();
};

defineExpose({
  open,
  close,
});
</script>

<template>
  <dialog ref="dialog">
    <header></header>
    <div>
      <slot></slot>
    </div>
    <div class="actions">
      <div class="spacer"></div>
      <SequencerButton @click="close">Close</SequencerButton>
    </div>
  </dialog>
</template>

<style lang="css" scoped>
dialog {
  color: oklch(92.2% 0.005 325.62);
  max-width: 600px;
  padding: 20px;
  border: 1px solid oklch(43.5% 0.029 321.78);
  border-radius: 16px;
  background: oklch(36.4% 0.029 323.89);
  display: grid;
  gap: 16px;
  grid-template-rows: min-content 1fr min-content;

  &:not([open]) {
    display: none;
  }

  .actions {
    display: flex;
    .spacer {
      flex: 1;
    }
  }
}
</style>
