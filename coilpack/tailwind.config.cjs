import {
  squirclePlugin,
  squircleRingColorPlugin,
  squircleRingPlugin,
} from "./src/plugins/squirclePlugin";
import colors from "tailwindcss/colors";
import defaultTheme from "tailwindcss/defaultTheme";
import lightsOutPlugin from "./src/plugins/lightsOutPlugin";

const themeCol = (variable) => `rgba(var(--color-${variable}), <alpha-value>)`;

module.exports = {
  mode: "jit",
  content: ["./index.html", "./src/**/*.{vue,js,ts,jsx,tsx}"],
  darkMode: "class",
  theme: {
    extend: {
      fontFamily: {
        sans: ["Radio Canada", ...defaultTheme.fontFamily.sans],
        header: ["Krona One", ...defaultTheme.fontFamily.sans],
        //https://fonts.google.com/specimen/Share+Tech+Mono
      },
      colors: {
        app: { background: themeCol("app-background") },
        header: {
          background: themeCol("header-background"),
          foreground: themeCol("header-foreground"),
          controls: themeCol("header-controls"),
        },
        controls: {
          background: themeCol("controls-background"),
        },
        container: {
          background: themeCol("container-background-base"),
          red: themeCol("container-background-red"),
          yellow: themeCol("container-background-yellow"),
          green: themeCol("container-background-green"),
          blue: themeCol("container-background-blue"),
          pink: themeCol("container-background-pink"),
          foreground: themeCol("container-foreground"),
        },
        control: {
          background: {
            base: {
              DEFAULT: themeCol("control-background-base-default"),
              highlight: themeCol("control-background-base-highlight"),
              dim: themeCol("control-background-base-dim"),
            },
            red: {
              DEFAULT: themeCol("control-background-red-default"),
              highlight: themeCol("control-background-red-highlight"),
              dim: themeCol("control-background-red-dim"),
            },
            yellow: {
              DEFAULT: themeCol("control-background-yellow-default"),
              highlight: themeCol("control-background-yellow-highlight"),
              dim: themeCol("control-background-yellow-dim"),
            },
            green: {
              DEFAULT: themeCol("control-background-green-default"),
              highlight: themeCol("control-background-green-highlight"),
              dim: themeCol("control-background-green-dim"),
            },
            blue: {
              DEFAULT: themeCol("control-background-blue-default"),
              highlight: themeCol("control-background-blue-highlight"),
              dim: themeCol("control-background-blue-dim"),
            },
            pink: {
              DEFAULT: themeCol("control-background-pink-default"),
              highlight: themeCol("control-background-pink-highlight"),
              dim: themeCol("control-background-pink-dim"),
            },
          },
          foreground: {
            base: {
              DEFAULT: themeCol("control-foreground-base-default"),
              highlight: themeCol("control-foreground-base-highlight"),
              dim: themeCol("control-foreground-base-dim"),
            },
            red: {
              DEFAULT: themeCol("control-foreground-red-default"),
              highlight: themeCol("control-foreground-red-highlight"),
              dim: themeCol("control-foreground-red-dim"),
            },
            yellow: {
              DEFAULT: themeCol("control-foreground-yellow-default"),
              highlight: themeCol("control-foreground-yellow-highlight"),
              dim: themeCol("control-foreground-yellow-dim"),
            },
            green: {
              DEFAULT: themeCol("control-foreground-green-default"),
              highlight: themeCol("control-foreground-green-highlight"),
              dim: themeCol("control-foreground-green-dim"),
            },
            blue: {
              DEFAULT: themeCol("control-foreground-blue-default"),
              highlight: themeCol("control-foreground-blue-highlight"),
              dim: themeCol("control-foreground-blue-dim"),
            },
            pink: {
              DEFAULT: themeCol("control-foreground-pink-default"),
              highlight: themeCol("control-foreground-pink-highlight"),
              dim: themeCol("control-foreground-pink-dim"),
            },
          },
        },
      },
      gap: {
        "controls-x": "var(--gap-controls-x, 1rem)",
        "controls-y": "var(--gap-controls-y, 2.25rem)",
      },
    },
  },
  plugins: [
    lightsOutPlugin,
    squirclePlugin,
    squircleRingPlugin,
    squircleRingColorPlugin,
    "prettier-plugin-tailwindcss",
  ],
};
