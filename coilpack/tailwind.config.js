const defaultTheme = require('tailwindcss/defaultTheme');
const colors = require('tailwindcss/colors');

const themeCol = (variable) => `rgba(var(--color-${ variable }), <alpha-value>)`;

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
        background: {
          50:  themeCol('background-50'),
          100: themeCol('background-100'),
          200: themeCol('background-200'),
          300: themeCol('background-300'),
          400: themeCol('background-400'),
          500: themeCol('background-500'),
          600: themeCol('background-600'),
          700: themeCol('background-700'),
          800: themeCol('background-800'),
          900: themeCol('background-900'),
        },
        foreground: {
          50:  themeCol('foreground-50'),
          100: themeCol('foreground-100'),
          200: themeCol('foreground-200'),
          300: themeCol('foreground-300'),
          400: themeCol('foreground-400'),
          500: themeCol('foreground-500'),
          600: themeCol('foreground-600'),
          700: themeCol('foreground-700'),
          800: themeCol('foreground-800'),
          900: themeCol('foreground-900'),
        },
        app: {background: themeCol('app-background')},
        container: {
          background: themeCol('container-background'),
          foreground: themeCol('container-foreground')
        },
        header: {
          background: themeCol('header-background')
        },
        control: {
          background: {
            base: {
              DEFAULT: themeCol('control-background-base-default'),
              highlight: themeCol('control-background-base-highlight'),
              dim: themeCol('control-background-base-dim'),
            },
            red: {
              DEFAULT: themeCol('control-background-red-default'),
              highlight: themeCol('control-background-red-highlight'),
              dim: themeCol('control-background-red-dim'),
            },
            yellow: {
              DEFAULT: themeCol('control-background-yellow-default'),
              highlight: themeCol('control-background-yellow-highlight'),
              dim: themeCol('control-background-yellow-dim'),
            },
            green: {
              DEFAULT: themeCol('control-background-green-default'),
              highlight: themeCol('control-background-green-highlight'),
              dim: themeCol('control-background-green-dim'),
            },
            blue: {
              DEFAULT: themeCol('control-background-blue-default'),
              highlight: themeCol('control-background-blue-highlight'),
              dim: themeCol('control-background-blue-dim'),
            },
            pink: {
              DEFAULT: themeCol('control-background-pink-default'),
              highlight: themeCol('control-background-pink-highlight'),
              dim: themeCol('control-background-pink-dim'),
            }
          },
          foreground: {
            base: {
              DEFAULT: themeCol('control-foreground-base-default'),
              highlight: themeCol('control-foreground-base-highlight'),
              dim: themeCol('control-foreground-base-dim'),
            },
            red: {
              DEFAULT: themeCol('control-foreground-red-default'),
              highlight: themeCol('control-foreground-red-highlight'),
              dim: themeCol('control-foreground-red-dim'),
            },
            yellow: {
              DEFAULT: themeCol('control-foreground-yellow-default'),
              highlight: themeCol('control-foreground-yellow-highlight'),
              dim: themeCol('control-foreground-yellow-dim'),
            },
            green: {
              DEFAULT: themeCol('control-foreground-green-default'),
              highlight: themeCol('control-foreground-green-highlight'),
              dim: themeCol('control-foreground-green-dim'),
            },
            blue: {
              DEFAULT: themeCol('control-foreground-blue-default'),
              highlight: themeCol('control-foreground-blue-highlight'),
              dim: themeCol('control-foreground-blue-dim'),
            },
            pink: {
              DEFAULT: themeCol('control-foreground-pink-default'),
              highlight: themeCol('control-foreground-pink-highlight'),
              dim: themeCol('control-foreground-pink-dim'),
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
