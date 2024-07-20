import { URL, fileURLToPath } from 'node:url'
import { defineConfig, loadEnv } from 'vite'
import basicSsl from '@vitejs/plugin-basic-ssl'
import { viteStaticCopy } from 'vite-plugin-static-copy'
import vue from '@vitejs/plugin-vue'

const env = loadEnv('mock', process.cwd(), '')
const configName = env['VITE_CONFIG']

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    viteStaticCopy({
      targets: [
        {
          src: `./configs/${configName}/*`,
          dest: `./configs/${configName}/`
        }
      ]
    }),
    basicSsl()
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  server: {
    port: 3000,
    strictPort: true
  },
  define: {
    'import.meta.env.VITE_BUILD_DATE': JSON.stringify(new Date().valueOf())
  }
})
