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
        header: ['Krona One', ...defaultTheme.fontFamily.sans]
        //https://fonts.google.com/specimen/Share+Tech+Mono
      },
      maxHeight: {
        'screen-75': '75vh'
      },
      colors: {
        foreground: colors.zinc,
        background: colors.zinc
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
      },
      backgroundImage: {
        'horizontal-split': "linear-gradient(to right, black 50% , theme(colors.background.800) 50%);"
      }
    }
  }
}
