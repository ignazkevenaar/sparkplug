export default {
    common: {
        background: {
            transparent: [
                "bg-transparent"
            ],
            default: [],
            outline: [
                "ring-2",
                "@squircle:squircle-ring"
            ],
            fill: []
        },
        foreground: {
            default: [],
            dim: []
        }
    },
    default: {
        background: {
            default: [
                "bg-button-background-base",
                "active:bg-button-background-base/50"
            ],
            outline: [
                "bg-button-background-base-dim",
                "active:bg-button-background-base-dim/50",
                "ring-button-background-base"
            ],
            fill: [
                "bg-button-background-base-highlight",
                "active:bg-button-background-base-highlight/75",
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-base"
            ],
            highlight: [
                "text-button-foreground-base-highlight"
            ],
            dim: [
                "text-button-foreground-base-dim"
            ]
        }
    },
    black: {
        background: {
            default: [],
            outline: [],
            fill: []
        },
        foreground: {
            default: [
                "text-black"
            ]
        }
    },
    red: {
        background: {
            default: [
                "bg-button-background-red",
                "active:bg-button-background-red/50"
            ],
            outline: [
                "bg-button-background-red-dim",
                "active:bg-button-background-red-dim/50",
                "ring-button-background-red"
            ],
            fill: [
                "bg-button-background-red-highlight",
                "active:bg-button-background-red-highlight/75",
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-red"
            ],
            highlight: [
                "text-button-foreground-red-highlight"
            ],
            dim: [
                "text-button-foreground-red-dim"
            ]
        }
    },
    yellow: {
        background: {
            default: [
                "bg-yellow-800/25"
            ],
            outline: [
                "bg-yellow-800/25",
                "ring-yellow-900"
            ],
            fill: [
                "bg-yellow-500",
                "active:bg-yellow-600",
                "ring-yellow-500"
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-yellow"
            ],
            highlight: [
                "text-button-foreground-yellow-highlight"
            ],
            dim: [
                "text-button-foreground-yellow-dim"
            ]
        }
    },
    green: {
        background: {
            default: [
                "bg-lime-800/25"
            ],
            outline: [
                "bg-lime-800/25",
                "ring-lime-900"
            ],
            fill: [
                "bg-lime-500",
                "active:bg-lime-600",
                "ring-lime-500"
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-green"
            ],
            highlight: [
                "text-button-foreground-green-highlight"
            ],
            dim: [
                "text-button-foreground-green-dim"
            ]
        }
    },
    blue: {
        background: {
            default: [
                "bg-blue-800/25"
            ],
            outline: [
                "bg-blue-800/25",
                "ring-blue-900"
            ],
            fill: [
                "bg-blue-500",
                "active:bg-blue-600",
                "ring-blue-500"
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-blue"
            ],
            highlight: [
                "text-button-foreground-blue-highlight"
            ],
            dim: [
                "text-button-foreground-blue-dim"
            ]
        }
    },
    pink: {
        background: {
            default: [
                "bg-pink-800/25"
            ],
            outline: [
                "bg-pink-800/25",
                "ring-pink-900"
            ],
            fill: [
                "bg-pink-500",
                "active:bg-pink-600",
                "ring-pink-500"
            ]
        },
        foreground: {
            default: [
                "text-button-foreground-pink"
            ],
            highlight: [
                "text-button-foreground-pink-highlight"
            ],
            dim: [
                "text-button-foreground-pink-dim"
            ]
        }
    }
};
