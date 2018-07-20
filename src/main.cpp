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
        unsigned char *message = (unsigned char*)malloc(sizeof(unsigned char) * 102);
        unsigned char *message_ptr = message;

        memset(message_ptr, 0xFF, 6);
	message_ptr += 6;

	for (int i = 0; i < 16; i++) 
        {
		memcpy(message_ptr, address, 6);
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