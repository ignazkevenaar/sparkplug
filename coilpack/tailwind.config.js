const defaultTheme = require('tailwindcss/defaultTheme');
const colors = require('tailwindcss/colors')

function withOpacity(variableName) {
  return ({ opacityValue }) => `rgba(var(${variableName}), ${ opacityValue ? opacityValue : 1 })`
}

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
        foreground: {
          50:  withOpacity('--color-foreground-50'),
          100: withOpacity('--color-foreground-100'),
          200: withOpacity('--color-foreground-200'),
          300: withOpacity('--color-foreground-300'),
          400: withOpacity('--color-foreground-400'),
          500: withOpacity('--color-foreground-500'),
          600: withOpacity('--color-foreground-600'),
          700: withOpacity('--color-foreground-700'),
          800: withOpacity('--color-foreground-800'),
          900: withOpacity('--color-foreground-900'),
        },
        background: {
          50:  withOpacity('--color-background-50'),
          100: withOpacity('--color-background-100'),
          200: withOpacity('--color-background-200'),
          300: withOpacity('--color-background-300'),
          400: withOpacity('--color-background-400'),
          500: withOpacity('--color-background-500'),
          600: withOpacity('--color-background-600'),
          700: withOpacity('--color-background-700'),
          800: withOpacity('--color-background-800'),
          900: withOpacity('--color-background-900'),
        },
        lightsOut: {
          50:  withOpacity('--color-lightsOut-50'),
          100: withOpacity('--color-lightsOut-100'),
          200: withOpacity('--color-lightsOut-200'),
          300: withOpacity('--color-lightsOut-300'),
          400: withOpacity('--color-lightsOut-400'),
          500: withOpacity('--color-lightsOut-500'),
          600: withOpacity('--color-lightsOut-600'),
          700: withOpacity('--color-lightsOut-700'),
          800: withOpacity('--color-lightsOut-800'),
          900: withOpacity('--color-lightsOut-900'),
        }
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
