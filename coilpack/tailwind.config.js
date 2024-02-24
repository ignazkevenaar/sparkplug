const defaultTheme = require('tailwindcss/defaultTheme');
const colors = require('tailwindcss/colors')

function withOpacity(variableName) {
  return ({ opacityValue }) => `rgba(var(${variableName}), ${ opacityValue ? opacityValue : 1 })`
}

const themeCol = (variable) => `rgba(var(--color-${ variable }), <alpha-value>)`

module.exports = {
  mode: 'jit',
  content: ['./index.html', './src/**/*.{vue,js,ts,jsx,tsx}'],
  darkMode: 'class',
  theme: {
    extend: {
      fontFamily: {
        sans: ['Radio Canada', ...defaultTheme.fontFamily.sans],
        header: ['Krona One', ...defaultTheme.fontFamily.sans],
        //https://fonts.google.com/specimen/Share+Tech+Mono
      },
      maxHeight: {
        'screen-75': '75vh'
      },
      colors: {
        background: themeCol('background'),
        container: {
          background: themeCol('container-background')
        },
        header: {
          background: themeCol('header-background')
        },
        button: {
          background: {
            base: {
              DEFAULT: themeCol('button-background-base-default'),
              highlight: themeCol('button-background-base-highlight'),
              dim: themeCol('button-background-base-dim'),
            },
            red: {
              DEFAULT: themeCol('button-background-red-default'),
              highlight: themeCol('button-background-red-highlight'),
              dim: themeCol('button-background-red-dim'),
            },
            yellow: {
              DEFAULT: themeCol('button-background-yellow-default'),
              highlight: themeCol('button-background-yellow-highlight'),
              dim: themeCol('button-background-yellow-dim'),
            },
            green: {
              DEFAULT: themeCol('button-background-green-default'),
              highlight: themeCol('button-background-green-highlight'),
              dim: themeCol('button-background-green-dim'),
            },
            blue: {
              DEFAULT: themeCol('button-background-blue-default'),
              highlight: themeCol('button-background-blue-highlight'),
              dim: themeCol('button-background-blue-dim'),
            },
            pink: {
              DEFAULT: themeCol('button-background-pink-default'),
              highlight: themeCol('button-background-pink-highlight'),
              dim: themeCol('button-background-pink-dim'),
            }
          },
          foreground: {
            base: {
              DEFAULT: themeCol('button-foreground-base-default'),
              highlight: themeCol('button-foreground-base-highlight'),
              dim: themeCol('button-foreground-base-dim'),
            },
            red: {
              DEFAULT: themeCol('button-foreground-red-default'),
              highlight: themeCol('button-foreground-red-highlight'),
              dim: themeCol('button-foreground-red-dim'),
            },
            yellow: {
              DEFAULT: themeCol('button-foreground-yellow-default'),
              highlight: themeCol('button-foreground-yellow-highlight'),
              dim: themeCol('button-foreground-yellow-dim'),
            },
            green: {
              DEFAULT: themeCol('button-foreground-green-default'),
              highlight: themeCol('button-foreground-green-highlight'),
              dim: themeCol('button-foreground-green-dim'),
            },
            blue: {
              DEFAULT: themeCol('button-foreground-blue-default'),
              highlight: themeCol('button-foreground-blue-highlight'),
              dim: themeCol('button-foreground-blue-dim'),
            },
            pink: {
              DEFAULT: themeCol('button-foreground-pink-default'),
              highlight: themeCol('button-foreground-pink-highlight'),
              dim: themeCol('button-foreground-pink-dim'),
            },
          }
        }
      },
      gap: {
        'controls-x': 'var(--gap-controls-x, 1rem)',
        'controls-y': 'var(--gap-controls-y, 2.25rem)',
      },
      gridRow: {
        'span-7':  'span 7 / span 7',
        'span-8':  'span 8 / span 8',
        'span-9':  'span 9 / span 9',
        'span-10': 'span 10 / span 10',
        'span-11': 'span 11 / span 11',
        'span-12': 'span 12 / span 12'
      },
      gridTemplateRows: {
       '8': 'repeat(8, minmax(0, 1fr))',
      }
    }
  },
  plugins: [
    require('./src/plugins/lightsOutPlugin'),
    require('./src/plugins/squirclePlugin').squirclePlugin,
    require('./src/plugins/squirclePlugin').squircleRingPlugin,
    require('./src/plugins/squirclePlugin').squircleRingColorPlugin,
  ]
}
