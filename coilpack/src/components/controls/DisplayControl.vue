<script setup lang="ts">
import type { CascadableProperties, DisplayControl, Segment, State } from '@/types/control.display'
import { computed, mergeProps, ref, watch } from 'vue'
import { Color } from '@/types/control'
import type { ControlModel } from '@/types/types'
import ErrorMessage from '../ErrorMessage.vue'
import InlineSvg from 'vue-inline-svg'
import type { Ref } from 'vue'
import { Style } from '@/types/control.display'
import colors from '../../styles/displayColors'

const config = import.meta.env.VITE_CONFIG || 'default'

const props = defineProps<{
  value: ControlModel
  control: DisplayControl
}>()

const errorLoading = ref(null)
const displayElement: Ref<Element | undefined> = ref()
const originalElementClassLists: Ref<string[][]> = ref([])

const SVGLoaded = (svgElement: Element) => {
  displayElement.value = svgElement

  props.control?.segments.forEach((segment) => {
    const segmentElements = svgElement.querySelectorAll(segment.selector)

    const originalClasses: string[] = []
    for (let i = 0; i < segmentElements?.length; i++) {
      originalClasses.push(segmentElements[i]?.getAttribute('class') || '')
    }

    originalElementClassLists.value.push(originalClasses)
  })

  appyIndicatorClasses(cascadedProps.value)
}

const currentStatesPerSegment = computed(() =>
  props.control.segments.map((segment) => {
    if (!segment.states) return []
    return segment.states.flatMap((state, index) => {
      const allModesApply = Object.keys(state.modes).every((mode) => {
        let positionValue = state.modes[mode]
        if (typeof positionValue === 'boolean') positionValue = Number(state.modes[mode]) * 255
        return props.value[mode] === positionValue
      })
      return allModesApply ? [{ ...state, index }] : []
    })
  })
)

const anyModeApplies = computed(() =>
  currentStatesPerSegment.value.map((segment) => !!segment.length)
)

const defaultProperties: CascadableProperties = {
  color: Color.default,
  style: Style.stroke
}

const cascadeProps = (segment: Segment, activeSegmentStates: State[]): CascadableProperties => {
  let mergedProps: CascadableProperties = { ...defaultProperties, ...segment }

  activeSegmentStates.forEach((activeSegmentState) => {
    mergedProps = { ...mergedProps, ...activeSegmentState }
  })

  return mergedProps
}

const cascadedProps = computed(() =>
  currentStatesPerSegment.value.map((states, segmentIndex) =>
    cascadeProps(props.control.segments[segmentIndex], states)
  )
)

const colorClassPerSegment = (props: CascadableProperties, anyMode: boolean) => {
  const onState = anyMode ? 'on' : 'off' //Replace 'off' with sensible state.

  return [...colors.common[props.style], ...(colors[props.color][onState] || [])]
}

const appyIndicatorClasses = (newSegmentsProps: CascadableProperties[]) => {
  if (errorLoading.value) return

  newSegmentsProps.forEach((segmentProps: CascadableProperties, index) => {
    const segment = props.control.segments[index]
    const activeSegmentElements = displayElement.value?.querySelectorAll(segment.selector) || []

    for (let i = 0; i < activeSegmentElements.length; i++) {
      const classes = colorClassPerSegment(segmentProps, anyModeApplies.value[index])
      activeSegmentElements[i].setAttribute(
        'class',
        originalElementClassLists.value[index][i] + ' ' + classes.join(' ')
      )
    }
  })
}

watch(cascadedProps, (newSegmentsProps) => {
  appyIndicatorClasses(newSegmentsProps)
})
</script>

<template>
  <div class="flex flex-1 flex-col">
    <ErrorMessage v-if="errorLoading" :error="errorLoading" title="" />
    <inline-svg
      v-else
      :src="`/configs/${config}/${control.path}`"
      class="display pointer-events-none relative grid flex-1 place-items-center fill-transparent stroke-2"
      @loaded="SVGLoaded($event)"
      @error="errorLoading = $event"
    />
  </div>
</template>

<style lang="scss">
#display {
  svg {
    position: absolute;
    height: 100%;
    width: 100%;
    max-height: 600px;
  }
}
</style>
