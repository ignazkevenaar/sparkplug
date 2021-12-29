#include "OTA.h"

const char *OTAHostName = "ESP8266";
const char *OTAPassword = "esp8266";

void setupOTA()
{
  // Setup OTA
  ArduinoOTA.setHostname(OTAHostName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart(onStartOTA);
  ArduinoOTA.onEnd(onEndOTA);
  ArduinoOTA.onProgress(onProgressOTA);
  ArduinoOTA.onError(onErrorOTA);

  ArduinoOTA.begin();
  Serial.println("OTA ready");
}

void onStartOTA()
{
  Serial.println("Start");
}

void onEndOTA()
{
  Serial.println("\nEnd");
}

void onProgressOTA(unsigned int progress, unsigned int total)
{
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void onErrorOTA(ota_error_t error)
{
  Serial.printf("Error[%u]: ", error);
  if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
  else if (error == OTA_BEGIN_ERROR)
    Serial.println("Begin Failed");
  else if (error == OTA_CONNECT_ERROR)
    Serial.println("Connect Failed");
  else if (error == OTA_RECEIVE_ERROR)
    Serial.println("Receive Failed");
  else if (error == OTA_END_ERROR)
    Serial.println("End Failed");
}
