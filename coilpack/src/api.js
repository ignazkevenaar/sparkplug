export let lightingModes;
export let controlsData;
export let connection;

let callbacks = {};

const fetchJSON = async (filename) => fetch(filename).then((r) => r.json());

export const fetchConfigurationFiles = async () =>
{
  lightingModes = await fetchJSON('/config/modes.json');
  controlsData = await fetchJSON('/config/controls.json');
}

const dispatch = (event_name, data) => {
  let chain = callbacks[event_name];
  if (typeof chain == 'undefined') return; // no callbacks for this event
  for (let i = 0; i < chain.length; i++) {
    chain[i](data)
  }
}

const bind = (event_name, callback) => {
  callbacks[event_name] = callbacks[event_name] || [];
  callbacks[event_name].push(callback);
  return this;
};

export const getModes = () =>
{
  connection?.send("G");
}

export const setMode = (inputArguments) =>
{
  connection?.send(`S:${ inputArguments.join(',') }`);
}

export const onGetMode = callback => {
  bind('M', callback);
}

export const setup = async () => {
  await fetchConfigurationFiles();

  if (process.env.NODE_ENV === "development") return true;

  return new Promise((resolve, reject) => {
    connection = new WebSocket('ws://' + window.location.hostname + ':81/');

    connection.onopen = () => {
      resolve(connection);
    };

    connection.onerror = error => {
      reject(error);
    };

    connection.onmessage = event =>
    {
      const splitData = event.data.split(" ");
      if (splitData.length != 2) return;

      const command = splitData[0];
      const inputArguments = splitData[1].split(',').filter(item => item);

      dispatch(command, inputArguments);
    };
  });
}
