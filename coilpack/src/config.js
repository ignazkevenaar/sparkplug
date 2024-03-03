const fetchJSON = async (filename) => fetch(filename).then((r) => r.json());

export default async () => {
  const configName = import.meta.env.VITE_CONFIG || "default";
  const config = await fetchJSON(`/configs/${configName}/config.json`);
  const lightingModes = await fetchJSON(`/configs/${configName}/modes.json`);
  const controlsConfig = await fetchJSON(
    `/configs/${configName}/controls.json`,
  );

  return {
    config,
    lightingModes,
    controlsConfig,
  };
};
