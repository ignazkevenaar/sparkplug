<script setup lang="ts">
import { type Ref, ref, watch } from 'vue'

interface IProps {
  modelValue: boolean
  title?: string
  clickOutsideToClose?: boolean
}

const props = withDefaults(defineProps<IProps>(), {
  modelValue: false,
  clickOutsideToClose: true
})

const emit = defineEmits<{
  'update:modelValue': [modeChange: boolean]
}>()

const dialog: Ref<HTMLDialogElement | null> = ref(null)

const show = () => {
  dialog.value?.showModal()

  // Push state to history
  const url = new URL(location.href)
  url.searchParams.set('dialog', 'open')
  history.pushState({}, '', url)
  window.addEventListener('popstate', close)

  document.body.style.overflow = 'hidden'
}

const close = () => {
  dialog.value?.close()

  // Push state to history
  const url = new URL(location.href)
  url.searchParams.delete('dialog')
  history.pushState({}, '', url)
  window.removeEventListener('popstate', close)

  document.body.style.overflow = ''
}

watch(
  () => props.modelValue,
  (newValue) => {
    if (newValue) show()
    else close()
  }
)

const clickHandler = (event: MouseEvent) => {
  if (event.target === dialog.value) close()
}
</script>

<template>
  <dialog
    ref="dialog"
    class="m-6 mt-auto hidden w-auto min-w-[300px] flex-col rounded-lg bg-dialog-background text-left text-base text-dialog-foreground backdrop:bg-dialog-backdrop/75 open:flex md:m-auto md:w-min"
    :open="modelValue"
    v-on="{ click: clickOutsideToClose ? clickHandler : undefined }"
    @close="emit('update:modelValue', false)"
  >
    <div>
      <div class="flex items-center gap-3 p-8">
        <button @click="close">
          <mdicon name="arrowLeft" />
        </button>
        <h2
          v-if="title"
          class="select-none overflow-hidden text-ellipsis whitespace-nowrap font-header text-lg"
          v-text="title"
        />
        <slot v-else name="header"></slot>
      </div>
      <div class="overflow-auto px-8">
        <slot></slot>
      </div>
      <div class="p-8 pt-4 text-right">
        <slot name="actions"></slot>
      </div>
    </div>
  </dialog>
</template>
