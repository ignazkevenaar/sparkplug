import type { ControlConfig, SparkplugConfig } from './types/config'

const fetchJSON = async <T>(input: RequestInfo | URL): Promise<T> =>
  fetch(input).then((response) => {
    if (!response.ok) {
      throw new Error(`Failed loading ${input}`)
    }
    return response.json()
  })

export async function loadConfiguration(): Promise<{
  config: SparkplugConfig
  lightingModes: string[]
  controlsConfig: ControlConfig
}> {
  const configName = import.meta.env.VITE_CONFIG || 'default'
  const config = await fetchJSON<SparkplugConfig>(`/configs/${configName}/config.json`)
  const lightingModes = await fetchJSON<string[]>(`/configs/${configName}/modes.json`)
  const controlsConfig = await fetchJSON<ControlConfig>(`/configs/${configName}/controls.json`)

  return {
    config,
    lightingModes,
    controlsConfig
  }
}
