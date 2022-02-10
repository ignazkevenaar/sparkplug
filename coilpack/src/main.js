import './index.css';
import * as mdijs from './config/icons';
import App from './App.vue';
import MasonryWall from '@yeger/vue-masonry-wall'
import { createApp } from 'vue'
import customIcons from './config/customIcons';
import mdiVue from 'mdi-vue/v3'

const app = createApp(App);

app.use(mdiVue, {
    icons: {
        ...mdijs,
        ...customIcons
    }
}).mount('#app');

app.use(MasonryWall);
