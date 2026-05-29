// eslint.config.js
import { defineConfig, includeIgnoreFile } from 'eslint/config'
import { fileURLToPath } from 'node:url'
import globals from 'globals'
import js from '@eslint/js'
import pluginVue from 'eslint-plugin-vue'
import skipFormatting from '@vue/eslint-config-prettier/skip-formatting'
import sortExports from 'eslint-plugin-sort-exports'
import vueTsConfig from '@vue/eslint-config-typescript'

const gitignorePath = fileURLToPath(new URL('.gitignore', import.meta.url))

export default defineConfig([
  includeIgnoreFile(gitignorePath, { gitignoreResolution: true }),
  js.configs.recommended,
  ...pluginVue.configs['flat/essential'],
  ...vueTsConfig(),
  skipFormatting,
  {
    plugins: {
      'sort-exports': sortExports
    },
    languageOptions: {
      ecmaVersion: 'latest',
      sourceType: 'module',
      globals: {
        ...globals.browser,
        ...globals.node
      }
    },
    rules: {
      'sort-imports': 'warn',
      'vue/max-attributes-per-line': 'off'
    }
  }
])
