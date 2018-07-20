#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <stdlib.h>
#include "server.h"
#include "globals.h"

ESP8266WebServer webserver(80);

static void handleRoot();
static void handleStatus();
static void handleNotFound();

static String writeJsonProperty(String key, String value, bool comma);

void setupWebserver()
{
	Serial.print("Starting webserver... ");
    webserver.on("/", handleRoot);
	webserver.on("/status", handleStatus);
	webserver.onNotFound(handleNotFound);

	webserver.begin();
	Serial.println("ok");
}

static void handleRoot()
{
	webserver.send(200, "text/plain", "ok");
}

static void handleStatus()
{
	String response;

	response.concat("{");
	response.concat(writeJsonProperty("targetIP", String(targetIP), true));
	response.concat(writeJsonProperty("targetMAC", String(targetMAC), true));
	response.concat(writeJsonProperty("packetFrequency", String(packetFrequency), true));
	response.concat(writeJsonProperty("lastPacketTime", String(lastPacketTime), false));
	response.concat("}\n");

	webserver.send(200, "application/json", response);
}

static void handleNotFound() 
{
    webserver.send(404, "text/plain", "");
}

static String writeJsonProperty(String key, String value, bool comma)
{
	String ret;

	ret.concat("\"");
	ret.concat(key);
	ret.concat("\":");

	ret.concat("\"");
	ret.concat(value);
	ret.concat("\"");

	if(comma)
		ret.concat(",");

	return ret;
}