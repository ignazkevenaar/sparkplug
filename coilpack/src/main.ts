import './styles/index.css'
import './styles/transitions.css'
import './styles/theme.scss'
import './styles/fonts.css'
import * as mdijs from './config/icons'
import App from './App.vue'
import { createApp } from 'vue'
import customIcons from './config/customIcons'
import mdiVue from 'mdi-vue/v3'
import squircle from '../../node_modules/css-houdini-squircle/squircle.min.js?url'

const app = createApp(App)

app
  .use(mdiVue, {
    icons: {
      ...mdijs,
      ...customIcons
    }
  })
  .mount('#app')

// TODO
declare namespace CSS {
  namespace paintWorklet {
    export function addModule(url: URL | string): void
  }
}

if ('paintWorklet' in CSS) {
  CSS.paintWorklet.addModule(squircle)
}
