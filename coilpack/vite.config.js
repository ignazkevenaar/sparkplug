import { defineConfig, loadEnv } from 'vite'
import { viteStaticCopy } from 'vite-plugin-static-copy'
import vue from '@vitejs/plugin-vue'

const env = loadEnv("mock", process.cwd(), "");
const configName = env['VITE_CONFIG'];

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    viteStaticCopy({
      targets: [
        {
          src: `./configs/${configName}/*`,
          dest: './config/'
        }
      ]
    })
  ],
  server: {
    port: 3000,
    strictPort: true
  }
})
