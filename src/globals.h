#ifndef __SUBTENO_GLOBALS
#define __SUBTENO_GLOBALS

// constants
extern const int BAUD;
extern const char* ssid;
extern const char* password;

extern const int WOL_PORT;

// mutables
extern char* targetMAC;
extern char* targetIP;
extern unsigned long packetFrequency;
extern unsigned long lastPacketTime;

#endif