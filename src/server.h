#ifndef __SUBTENO_SERVER
#define __SUBTENO_SERVER

#include <ESP8266WebServer.h>

extern ESP8266WebServer webserver;

void setupWebserver();

extern char* targetMAC;
extern char* targetIP;
extern unsigned long packetFrequency;

#endif