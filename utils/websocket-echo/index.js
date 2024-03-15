const WebSocket = require("ws");

let port = 8080;

if (process.argv.length >= 4 && process.argv[2] === "--port") {
  port = Number(process.argv[3]);
}

const wss = new WebSocket.Server({ port });

wss.on("connection", (ws) => {
  ws.on("error", console.error);

  ws.on("message", function message(data) {
    console.log("received: %s", data);

    ws.send(data.toString());
  });
});

console.log(`Listening on ws://localhost:${port}`);
