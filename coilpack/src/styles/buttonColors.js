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
                "bg-background-600",
                "active:bg-background-800"
            ],
            outline: [
                "bg-background-700",
                "active:bg-background-800"
            ],
            fill: [
                "bg-foreground-50",
                "active:bg-foreground-100",
                "lo:bg-lightsOut-400",
            ]
        },
        foreground: {
            default: [
                "lo:text-lightsOut-300"
            ],
            dim: [
                "text-foreground-50/10"
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
                "bg-red-900/25"
            ],
            outline: [
                "bg-red-900/25",
                "ring-red-900",
            ],
            fill: [
                "bg-red-600",
                "active:bg-red-700"
            ]
        },
        foreground: {
            default: [
                "text-red-500"
            ],
            dim: [
                "text-red-900/25"
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
                "text-yellow-500"
            ],
            dim: [
                "text-yellow-900/25"
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
                "text-lime-500"
            ],
            dim: [
                "text-green-900/25"
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
                "text-blue-500"
            ],
            dim: [
                "text-blue-900/25"
            ]
        }
    }
};
