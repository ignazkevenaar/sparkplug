/* eslint-env node */
require('@rushstack/eslint-patch/modern-module-resolution')

module.exports = {
  root: true,
  extends: [
    'plugin:vue/vue3-essential',
    'eslint:recommended',
    '@vue/eslint-config-typescript',
    '@vue/eslint-config-prettier/skip-formatting'
  ],
  parserOptions: {
    ecmaVersion: 'latest'
  },
  plugins: ['sort-exports'],
  rules: {
    'sort-imports': 'warn',
    'vue/max-attributes-per-line': 'off'
  },
  env: { browser: true, es2020: true, node: true }
}
