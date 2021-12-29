#pragma once

#include <Arduino.h>

#include <WebSocketsServer.h>

extern uint16_t portWebSockets;

void setupWebSockets();
void updateWebSockets();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void socketConnectionChanged(uint8_t connectedClients_);
bool onSocketConnectionChanged(uint8_t connectedClients_);
