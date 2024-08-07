export default {
  common: {
    background: {
      transparent: ["bg-transparent"],
      default: [],
      outline: ["ring-2", "@squircle:squircle-ring"],
      fill: [],
    },
    foreground: {
      default: [],
      dim: [],
    },
  },
  default: {
    background: {
      default: [
        "bg-control-background-base",
        "active:bg-control-background-base/50",
      ],
      outline: [
        "bg-control-background-base-dim",
        "active:bg-control-background-base-dim/50",
        "ring-control-background-base",
      ],
      fill: [
        "bg-control-background-base-highlight",
        "active:bg-control-background-base-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-base"],
      highlight: ["text-control-foreground-base-highlight"],
      dim: ["text-control-foreground-base-dim"],
    },
  },
  black: {
    background: {
      default: [],
      outline: [],
      fill: [],
    },
    foreground: {
      default: ["text-black"],
    },
  },
  red: {
    background: {
      default: [
        "bg-control-background-red",
        "active:bg-control-background-red/50",
      ],
      outline: [
        "bg-control-background-red-dim",
        "active:bg-control-background-red-dim/50",
        "ring-control-background-red",
      ],
      fill: [
        "bg-control-background-red-highlight",
        "active:bg-control-background-red-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-red"],
      highlight: ["text-control-foreground-red-highlight"],
      dim: ["text-control-foreground-red-dim"],
    },
  },
  yellow: {
    background: {
      default: [
        "bg-control-background-yellow",
        "active:bg-control-background-yellow/50",
      ],
      outline: [
        "bg-control-background-yellow-dim",
        "active:bg-control-background-yellow-dim/50",
        "ring-control-background-yellow",
      ],
      fill: [
        "bg-control-background-yellow-highlight",
        "active:bg-control-background-yellow-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-yellow"],
      highlight: ["text-control-foreground-yellow-highlight"],
      dim: ["text-control-foreground-yellow-dim"],
    },
  },
  green: {
    background: {
      default: [
        "bg-control-background-green",
        "active:bg-control-background-green/50",
      ],
      outline: [
        "bg-control-background-green-dim",
        "active:bg-control-background-green-dim/50",
        "ring-control-background-green",
      ],
      fill: [
        "bg-control-background-green-highlight",
        "active:bg-control-background-green-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-green"],
      highlight: ["text-control-foreground-green-highlight"],
      dim: ["text-control-foreground-green-dim"],
    },
  },
  blue: {
    background: {
      default: [
        "bg-control-background-blue",
        "active:bg-control-background-blue/50",
      ],
      outline: [
        "bg-control-background-blue-dim",
        "active:bg-control-background-blue-dim/50",
        "ring-control-background-blue",
      ],
      fill: [
        "bg-control-background-blue-highlight",
        "active:bg-control-background-blue-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-blue"],
      highlight: ["text-control-foreground-blue-highlight"],
      dim: ["text-control-foreground-blue-dim"],
    },
  },
  pink: {
    background: {
      default: [
        "bg-control-background-pink",
        "active:bg-control-background-pink/50",
      ],
      outline: [
        "bg-control-background-pink-dim",
        "active:bg-control-background-pink-dim/50",
        "ring-control-background-pink",
      ],
      fill: [
        "bg-control-background-pink-highlight",
        "active:bg-control-background-pink-highlight/75",
      ],
    },
    foreground: {
      default: ["text-control-foreground-pink"],
      highlight: ["text-control-foreground-pink-highlight"],
      dim: ["text-control-foreground-pink-dim"],
    },
  },
};
