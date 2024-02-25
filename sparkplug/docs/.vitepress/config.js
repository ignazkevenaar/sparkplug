module.exports = {
  title: "Sparkplug",
  head: [
    ["link", { rel: "icon", type: "image/svg+xml", href: "/logo.svg" }],
    [
      "link",
      {
        rel: "stylesheet",
        crossorigin: "anonymous",
        href: "https://fonts.googleapis.com/css2?family=Krona+One&display=swap",
      },
    ],
  ],
  themeConfig: {
    logo: "/logo.svg",
    nav: [
      { text: "Home", link: "/" },
      { text: "Guide", link: "/guide/" },
      { text: "Reference", link: "/reference/" },
      { text: "GitHub", link: "https://github.com/ignazkevenaar/sparkplug" },
    ],
  },
  home: true,
};
// https://github.com/vitejs/vite/blob/main/docs/.vitepress/config.js
