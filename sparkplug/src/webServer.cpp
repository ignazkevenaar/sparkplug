#include "webServer.h"

uint16_t portHTTP = 80;

ESP8266WebServer server = ESP8266WebServer(portHTTP);

void setupWebServer()
{
    LittleFS.begin();
    server.onNotFound(handleNotFound);
    server.begin();
}

void updateWebServer()
{
    server.handleClient();
}

String getContentType(String filename)
{
    // Convert the file extension to the MIME type.
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    return "text/plain";
}

void handleNotFound()
{
    String path = server.uri();
    if (path.endsWith("/")) path += "index.html";
    String contentType = getContentType(path);

    Serial.println(path);

    if (LittleFS.exists(path))
    {
        File file = LittleFS.open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        file.close();
        return;
    }

    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}
