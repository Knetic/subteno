#include "globals.h"

// CONFIGURED SECRET THINGS;
const char* ssid = "";
const char* password = "";
char* targetMAC = (char*)"";

// constants
const int BAUD = 9600;
const int WOL_PORT = 9;

// mutables
char* targetIP = (char*)"192.168.1.255"; // the usual LAN broadcast IP
unsigned long packetFrequency = 10000;
unsigned long lastPacketTime;