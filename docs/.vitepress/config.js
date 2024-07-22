module.exports = {
  title: "Sparkplug",
  base: "/sparkplug/",
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
      { text: "Guide", link: "/guide/introduction" },
      { text: "Reference", link: "/reference/" },
      { text: "Coilpack", link: "/coilpack" },
      { text: "GitHub", link: "https://github.com/ignazkevenaar/sparkplug" },
    ],
    sidebar: [
      {
        text: "Guide",
        items: [
          { text: "Introduction", link: "/guide/introduction" },
          { text: "Getting Started", link: "/guide/getting-started" },
        ],
      },
      {
        text: "Essentials",
        items: [
          { text: "Creating a Config", link: "/guide/config" },
          { text: "Defining Modes", link: "/guide/modes" },
          { text: "Setting up Devices", link: "/guide/devices" },
          { text: "Adding Presets", link: "/guide/presets" },
          {
            text: "Assigning Presets to Channels",
            link: "/guide/presets-channels",
          },
          {
            text: "Compiling and Uploading",
            link: "/guide/compiling-uploading",
          },
        ],
      },
      {
        text: "Presets in depth",
        items: [
          { text: "Cascading presets", link: "/guide/cascading" },
          { text: "Blinkers", link: "/guide/blinkers" },
          { text: "Sequential Blinkers", link: "/guide/sequential-blinkers" },
          { text: "US tail lights", link: "/guide/us-tail-lights" },
        ],
      },
      {
        text: "Coilpack",
        items: [
          { text: "Creating a Config", link: "/" },
          { text: "Setting up Controls", link: "/" },
          { text: "Building and Uploading", link: "/" },
        ],
      },
      {
        text: "Extra Topics",
        items: [{ text: "Adding a filesystem", link: "/guide/littlefs" }],
      },
    ],
    footer: {
      copyright: `Copyright © ${new Date().getFullYear()} Ignaz Kevenaar`,
    },
  },
};
