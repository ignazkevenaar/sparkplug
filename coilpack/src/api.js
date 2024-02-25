export let config;
export let lightingModes;
export let controlsData;
export let connection;

let callbacks = {};

const fetchJSON = async (filename) => fetch(filename).then((r) => r.json());

export const fetchConfigurationFiles = async () => {
  const configName = import.meta.env.VITE_CONFIG || "default";
  config = await fetchJSON(`/configs/${configName}/config.json`);
  lightingModes = await fetchJSON(`/configs/${configName}/modes.json`);
  controlsData = await fetchJSON(`/configs/${configName}/controls.json`);
};

const dispatch = (event_name, data) => {
  let chain = callbacks[event_name];
  if (typeof chain == "undefined") return; // no callbacks for this event
  for (let i = 0; i < chain.length; i++) {
    chain[i](data);
  }
};

const bind = (event_name, callback) => {
  callbacks[event_name] = callbacks[event_name] || [];
  callbacks[event_name].push(callback);
  return this;
};

const trySend = (data) => {
  const OPEN = 1;
  if (connection?.readyState !== OPEN) return;
  connection.send(data);
};

export const getModes = () => {
  trySend("G");
};

export const setMode = (inputArguments) => {
  trySend(`S ${inputArguments.join(",")}`);
};

export const unsetMode = (inputArguments) => {
  trySend(`U ${inputArguments.join(",")}`);
};

export const onGetMode = (callback) => {
  bind("M", callback);
};

export const setup = async () => {
  await fetchConfigurationFiles();

  return new Promise((resolve, reject) => {
    if (import.meta.env.DEV) {
      const debugServer = import.meta.env.VITE_DEBUG_WEBSOCKET;
      if (!debugServer) return false;
      connection = new WebSocket(debugServer);
    } else {
      connection = new WebSocket("ws://" + window.location.hostname + ":81/");
    }

    connection.onopen = () => {
      console.log(connection);
      resolve(connection);
    };

    connection.onerror = (error) => {
      reject(error);
    };

    connection.onmessage = (event) => {
      console.log("websocket says:", event.data);

      const splitData = event.data.split(" ");
      if (splitData.length != 2) return;

      const command = splitData[0];
      const inputArguments = splitData[1].split(",").filter((item) => item);

      dispatch(command, inputArguments);
    };
  });
};
