#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <string.h>
#include "server.h"
#include "globals.h"

MDNSResponder mdns;
WiFiUDP udp;

static void setupWifi();
static void sendPacket();
static unsigned char* createPacket(const char* address);
static void blink(int count, int interval);

static size_t get_hex_from_string(const char *buf, size_t buflen, unsigned *hex);
static int get_ether(const char *hardware_addr, unsigned char *dest);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

	Serial.begin(BAUD);
	Serial.println("subteno system initializing");

        setupWifi();
        setupWebserver();

        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("system ready.");
        blink(3, 100);
}

void loop()
{
        unsigned long current, diff;

        webserver.handleClient();

        current = millis();
        diff = current - lastPacketTime;

        if(diff >= packetFrequency)
        {
                sendPacket();
                lastPacketTime = current;
        }
}

static void setupWifi()
{
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.print("... ");

        WiFi.begin(ssid, password);
        
        while (WiFi.status() != WL_CONNECTED) 
                delay(500);

        Serial.println("ok");

        //
        Serial.print("Starting MDNS responder... ");

        if (mdns.begin("subteno", WiFi.localIP()))
                Serial.println("ok");
        else
        {
                Serial.println("failed.");
                while(1){delay(1000);}
        }

        Serial.print("Acquired IP: ");
        Serial.println(WiFi.localIP());
}

static void sendPacket()
{
        unsigned char* packet;

        blink(1, 100);
        packet = createPacket(targetMAC);

        udp.beginPacket(targetIP, WOL_PORT);
        for(int i = 0; i < 102; i++)
                udp.write(packet[i]);
        udp.endPacket();
}

static unsigned char* createPacket(const char* address)
{
        unsigned char* message = (unsigned char*)malloc(sizeof(unsigned char) * 102);
        unsigned char* message_ptr = message;
        unsigned char* mac = (unsigned char*)malloc(sizeof(unsigned char) * 6);

        get_ether(address, mac);

        // six 0xFF's
        memset(message_ptr, 0xFF, 6);
	message_ptr += 6;

        // followed by 16 repetitions of the 48-bit (6-byte) MAC of the target
	for (int i = 0; i < 16; i++) 
        {
		memcpy(message_ptr, mac, 6);
		message_ptr += 6;
	}

        return message;
}

static void blink(int count, int interval)
{
	for(int i = 0; i < count; i++)
	{
		digitalWrite(LED_BUILTIN, LOW);
		delay(interval);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(interval);
	}
}

// ref: https://github.com/scratch-org/wol.c/
static size_t get_hex_from_string(const char *buf, size_t buflen, unsigned *hex)
{
	size_t i;

	*hex = 0;
	for (i = 0; i < buflen && buf[i] != '\0'; ++i) {
		*hex <<= 4;
		if (isdigit(buf[i])) {
			*hex |= buf[i] - '0';
		} else if (buf[i] >= 'a' && buf[i] <= 'f') {
			*hex |= buf[i] - 'a' + 10;
		} else if (buf[i] >= 'A' && buf[i] <= 'F') {
			*hex |= buf[i] - 'A' + 10;
		} else {
			return 0; /* Error */
		}
	}
	return i;
}

// ref: https://github.com/scratch-org/wol.c/
static int get_ether(const char *hardware_addr, unsigned char *dest)
{
	const char *orig = hardware_addr;
	size_t i;

	for (i = 0; *hardware_addr != '\0' && i < 6; ++i) {
		/* Parse two characters at a time. */
		unsigned hex;
		size_t chars_read = get_hex_from_string(hardware_addr, 2, &hex);
		if (chars_read == 0) {
			return -1;
		} else {
			hardware_addr += chars_read;
		}

		*dest++ = (unsigned char)(hex & 0xFF);

		/* We might get a colon here, but it is not required. */
		if (*hardware_addr == ':') ++hardware_addr;
	}

	return (hardware_addr - orig == 17) ? 0 : -1;
}