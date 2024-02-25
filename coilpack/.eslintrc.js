module.exports = {
  extends: ["plugin:vue/vue3-recommended"],
  plugins: ["sort-exports"],
  rules: {
    "sort-imports": "warn",
    "vue/max-attributes-per-line": "off",
  },
};
