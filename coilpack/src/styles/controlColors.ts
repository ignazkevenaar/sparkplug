export default {
  common: {
    background: {
      default: [],
      outline: ['ring-2'],
      fill: ['shadow-glow']
    },
    foreground: {
      default: [],
      highlight: [],
      dim: []
    }
  },
  default: {
    background: {
      default: [
        'shadow-xl',
        'bg-linear-to-b from-background-700 via-background-800/75 to-background-700/75 via-70%',
        'enabled:active:from-background-700/75 enabled:active:via-background-800/50 enabled:active:to-background-700/50',
        'inset-shadow-rim inset-shadow-background-400 enabled:active:inset-shadow-background-500'
      ],
      outline: ['bg-background-800', 'enabled:active:bg-background-800/50', 'ring-base'],
      fill: ['bg-background-100', 'enabled:active:bg-background-100/75']
    },
    foreground: {
      default: ['text-foreground-200'],
      highlight: ['text-foreground-50'],
      dim: ['text-foreground-800']
    }
  },
  transparent: {
    background: {
      transparent: [],
      default: ['bg-transparent'],
      outline: ['bg-transparent'],
      fill: ['bg-transparent']
    },
    foreground: {
      default: ['text-transparent'],
      highlight: ['text-transparent'],
      dim: ['text-transparent']
    }
  },
  black: {
    background: {
      default: [],
      outline: [],
      fill: []
    },
    foreground: {
      default: ['text-black'],
      highlight: ['text-black'],
      dim: ['text-black']
    }
  },
  red: {
    background: {
      default: ['bg-red', 'enabled:active:bg-red/50'],
      outline: ['bg-red-dim', 'enabled:active:bg-red-dim/50', 'ring-red'],
      fill: ['bg-red-highlight', 'enabled:active:bg-red-highlight/75', 'shadow-red/50']
    },
    foreground: {
      default: ['text-red'],
      highlight: ['text-red-highlight'],
      dim: ['text-red-dim']
    }
  },
  yellow: {
    background: {
      default: ['bg-yellow', 'enabled:active:bg-yellow/50'],
      outline: ['bg-yellow-dim', 'enabled:active:bg-yellow-dim/50', 'ring-yellow'],
      fill: ['bg-yellow-highlight', 'enabled:active:bg-yellow-highlight/75', 'shadow-yellow/50']
    },
    foreground: {
      default: ['text-yellow'],
      highlight: ['text-yellow-highlight'],
      dim: ['text-yellow-dim']
    }
  },
  green: {
    background: {
      default: ['bg-green', 'enabled:active:bg-green/50'],
      outline: ['bg-green-dim', 'enabled:active:bg-green-dim/50', 'ring-green'],
      fill: [
        'linear-to-br from-green to-green-highlight',
        'enabled:active:bg-green-highlight/75',
        'shadow-green/50'
      ]
    },
    foreground: {
      default: ['text-green'],
      highlight: ['text-green-highlight'],
      dim: ['text-green-dim']
    }
  },
  blue: {
    background: {
      default: ['bg-blue', 'enabled:active:bg-blue/50'],
      outline: ['bg-blue-dim', 'enabled:active:bg-blue-dim/50', 'ring-blue'],
      fill: ['bg-blue-highlight', 'enabled:active:bg-blue-highlight/75', 'shadow-blue/50']
    },
    foreground: {
      default: ['text-blue'],
      highlight: ['text-blue-highlight'],
      dim: ['text-blue-dim']
    }
  },
  pink: {
    background: {
      default: ['bg-pink', 'enabled:active:bg-pink/50'],
      outline: ['bg-pink-dim', 'enabled:active:bg-pink-dim/50', 'ring-pink'],
      fill: ['bg-pink-highlight', 'enabled:active:bg-pink-highlight/75', 'shadow-pink/50']
    },
    foreground: {
      default: ['text-pink'],
      highlight: ['text-pink-highlight'],
      dim: ['text-pink-dim']
    }
  }
}
