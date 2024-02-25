module.exports = {
  extends: ["plugin:vue/vue3-recommended", "plugin:tailwindcss/recommended"],
  plugins: ["tailwindcss", "sort-exports"],
  rules: {
    "sort-imports": "warn",
    "tailwindcss/classnames-order": [
      "warn",
      {
        officialSorting: true,
      },
    ],
    "tailwindcss/no-custom-classname": "off",
  },
};
