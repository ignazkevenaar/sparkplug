const plugin = require("tailwindcss/plugin");
const {
  default: flattenColorPalette,
} = require("tailwindcss/lib/util/flattenColorPalette");
const {
  default: withAlphaVariable,
} = require("tailwindcss/lib/util/withAlphaVariable");

const baseStyles = {
  "mask-image": "paint(squircle)",
  "--squircle-smooth": ".8",
};

const squirclePlugin = plugin(
  function ({ matchUtilities, addVariant, theme }) {
    matchUtilities(
      {
        squircle: (value) => ({
          ...baseStyles,
          "--squircle-radius": value,
        }),
      },
      { values: theme("squircle") },
    ),
      addVariant("@squircle", "@supports (mask-image: paint(squircle))");
  },
  {
    theme: {
      squircle: {
        none: "0px",
        sm: "2px",
        DEFAULT: "4px",
        md: "6px",
        lg: "8px",
        xl: "12px",
        "2xl": "16px",
        "3xl": "24px",
      },
    },
  },
);

const squircleRingPlugin = plugin(
  function ({ matchUtilities, theme }) {
    matchUtilities(
      {
        "squircle-ring": (value) => ({
          position: "relative",
          "&::after": {
            content: "''",
            display: "block",
            inset: "0",
            position: "absolute",
            mask: "paint(squircle)",
            "--squircle-outline": value,
            background: "var(--tw-squircle-ring-color)",
            opacity: "var(--tw-squircle-ring-opacity)",
            "pointer-events": "none",
            "--squircle-radius": "inherit",
          },
        }),
      },
      { values: theme("squircleRing") },
    );
  },
  {
    theme: {
      squircleRing: {
        0: "0",
        1: "1px",
        2: "2px",
        DEFAULT: "3px",
        4: "4px",
        8: "8px",
      },
    },
  },
);

const squircleRingColorPlugin = plugin(function ({
  matchUtilities,
  theme,
  corePlugins,
}) {
  matchUtilities(
    {
      ring: (value) => {
        if (!corePlugins("ringOpacity")) {
          return {
            "--tw-squircle-ring-color": toColorValue(value),
          };
        }

        return withAlphaVariable({
          color: value,
          property: "--tw-squircle-ring-color",
          variable: "--tw-squircle-ring-opacity",
        });
      },
    },
    {
      values: Object.fromEntries(
        Object.entries(flattenColorPalette(theme("ringColor"))).filter(
          ([modifier]) => modifier !== "DEFAULT",
        ),
      ),
      type: "color",
    },
  );
});

module.exports = {
  squirclePlugin,
  squircleRingPlugin,
  squircleRingColorPlugin,
};
