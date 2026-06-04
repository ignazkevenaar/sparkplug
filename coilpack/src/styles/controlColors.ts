export default {
  common: {
    background: {
      default: [],
      outline: ['ring-2'],
      fill: ['bg-radial-[at_50%_75%] shadow-glow from-25%']
    },
    foreground: {
      default: ['drop-shadow-xs drop-shadow-black/25'],
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
      default: ['text-black', 'drop-shadow-none!'],
      highlight: ['text-black', 'drop-shadow-none!'],
      dim: ['text-black', 'drop-shadow-none!']
    }
  },
  red: {
    background: {
      default: ['bg-red-600', 'enabled:active:bg-red-600/50'],
      outline: ['bg-red-950', 'enabled:active:bg-red-950/50', 'ring-red-600'],
      fill: [
        'from-red-500 to-red-600',
        'enabled:active:from-red-500/95 enabled:active:to-red-600/95',
        'shadow-red-600/50'
      ]
    },
    foreground: {
      default: ['text-red-500'],
      highlight: ['text-red-400'],
      dim: ['text-red-950']
    }
  },
  yellow: {
    background: {
      default: ['bg-amber-500', 'enabled:active:bg-amber-500/50'],
      outline: ['bg-amber-950', 'enabled:active:bg-amber-950/50', 'ring-amber-500'],
      fill: [
        'from-amber-400 to-amber-500',
        'enabled:active:from-amber-400/95 enabled:active:to-amber-500/95',
        'shadow-amber-500/50'
      ]
    },
    foreground: {
      default: ['text-amber-500'],
      highlight: ['text-amber-400'],
      dim: ['text-amber-950']
    }
  },
  green: {
    background: {
      default: ['bg-lime-500', 'enabled:active:bg-lime-500/50'],
      outline: ['bg-lime-950', 'enabled:active:bg-lime-950/50', 'ring-lime-500'],
      fill: [
        'from-lime-400 to-lime-500',
        'enabled:active:from-lime-400/95 enabled:active:to-lime-500/95',
        'shadow-lime-500/50'
      ]
    },
    foreground: {
      default: ['text-lime-500'],
      highlight: ['text-lime-400'],
      dim: ['text-lime-950']
    }
  },
  blue: {
    background: {
      default: ['bg-blue-400', 'enabled:active:bg-blue-400/50'],
      outline: ['bg-blue-950', 'enabled:active:bg-blue-950/50', 'ring-blue-400'],
      fill: [
        'from-blue-300 to-blue-400',
        'enabled:active:from-blue-300/95 enabled:active:to-blue-400/95',
        'shadow-blue-400/50'
      ]
    },
    foreground: {
      default: ['text-blue-500'],
      highlight: ['text-blue-400'],
      dim: ['text-blue-950']
    }
  },
  pink: {
    background: {
      default: ['bg-pink-500', 'enabled:active:bg-pink/50'],
      outline: ['bg-pink-950', 'enabled:active:bg-pink-950/50', 'ring-pink'],
      fill: [
        'from-pink-400 to-pink-500',
        'enabled:active:from-pink-400/95 enabled:active:to-pink-500/95',
        'shadow-pink-500/50'
      ]
    },
    foreground: {
      default: ['text-pink-500'],
      highlight: ['text-pink-400'],
      dim: ['text-pink-950']
    }
  }
}
