<script>
import { h } from 'vue'

export default {
  props: {
    src: { type: String, required: true }
  },
  data() {
    return {
      svgElement: null
    }
  },
  async mounted() {
    let svg = await fetch(this.src).then(r => r.text());
    this.svgElement = svg;
  },
  render: function() {
    // if (this.svgElement) return h('div', {
    //   innerHTML: this.svgElement
    // });

    if (this.svgElement) return h('div', {
      innerHTML: this.svgElement
    });

    return null;
  }
};
</script>
