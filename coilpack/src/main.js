import './index.css';
import * as mdijs from './config/icons';
import App from './App.vue';
import { createApp } from 'vue'
import customIcons from './config/customIcons';
import mdiVue from 'mdi-vue/v3'

const app = createApp(App).use(mdiVue, {
    icons: {...mdijs, ...customIcons}
}).mount('#app');
