export let connection;

let callbacks = {};

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

export const unsetAllModes = () => {
  trySend(`U`);
};

export const onGetMode = (callback) => {
  bind("M", callback);
};

export const setup = async () => {
  return new Promise((resolve, reject) => {
    if (import.meta.env.DEV) {
      const debugServer = import.meta.env.VITE_DEBUG_WEBSOCKET;
      if (!debugServer)
        throw new Error(
          "Debug websocket server not defined! Use environment variable: VITE_DEBUG_WEBSOCKET",
        );
      connection = new WebSocket(debugServer);
    } else {
      connection = new WebSocket("ws://" + window.location.hostname + ":81/");
    }

    connection.onmessage = (event) => {
      if (import.meta.env.DEV) {
        console.log("Websocket says:", event.data);
      }

      const splitData = event.data.split(" ");
      if (splitData.length != 2) return;

      const command = splitData[0];
      const inputArguments = splitData[1].split(",").filter((item) => item);

      dispatch(command, inputArguments);
    };

    resolve(connection);
  });
};
