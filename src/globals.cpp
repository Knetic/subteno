#include "globals.h"

// CONFIGURED SECRET THINGS;
const char* ssid = "";
const char* password = "";
char* targetMAC = (char*)"";
char* targetIP = (char*)"";

// constants
const int BAUD = 9600;
const int WOL_PORT = 9;

// mutables
unsigned long packetFrequency = 10000;
unsigned long lastPacketTime;