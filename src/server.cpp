#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "server.h"

ESP8266WebServer webserver(80);

char* targetMAC = "";
char* targetIP = "";
unsigned long packetFrequency = 10000;

void setupHandlers(ESP8266WebServer);
void handleRoot();
void handleNotFound();

void setupWebserver()
{
	Serial.print("Starting webserver... ");
    webserver.on("/", handleRoot);
	webserver.onNotFound(handleNotFound);

	webserver.begin();
	Serial.println("ok");
}

void handleRoot()
{
	webserver.send(200, "text/plain", "ok");
}

void handleNotFound() 
{
    webserver.send(404, "text/plain", "");
}