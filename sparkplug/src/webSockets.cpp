#include "webSockets.h"

#include "input.h"

uint16_t portWebSockets = 81;
WebSocketsServer webSocketsServer = WebSocketsServer(portWebSockets);
uint8_t connectedClients = 0;

void setupWebSockets()
{
  webSocketsServer.begin();
  webSocketsServer.onEvent(webSocketEvent);
}

void updateWebSockets()
{
  webSocketsServer.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
  {
    connectedClients--;
    socketConnectionChanged(connectedClients);
  }
  break;
  case WStype_CONNECTED:
  {
    connectedClients++;
    socketConnectionChanged(connectedClients);

    IPAddress ip = webSocketsServer.remoteIP(num);
  }
  break;
  case WStype_TEXT:
    splitMessage((char *)payload, length);
    webSocketsServer.broadcastTXT((const uint8_t *)outputBuffer.getBuffer(), (size_t)outputBuffer.size());
    break;
  }
}

void socketConnectionChanged(uint8_t connectedClients)
{
  onSocketConnectionChanged(connectedClients)
}

__attribute__((weak)) void onSocketConnectionChanged(uint8_t connectedClients)
{
}
