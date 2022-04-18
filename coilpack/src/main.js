import './styles/index.css';
import './styles/transitions.css';
import * as mdijs from './config/icons';
import App from './App.vue';
import { createApp } from 'vue'
import customIcons from './config/customIcons';
import mdiVue from 'mdi-vue/v3'
import squircle from '../../node_modules/css-houdini-squircle/squircle.min.js?url';

const app = createApp(App);

app.use(mdiVue, {
    icons: {
        ...mdijs,
        ...customIcons
    }
}).mount('#app');

if ('paintWorklet' in CSS) {
    CSS.paintWorklet.addModule(squircle);
}
