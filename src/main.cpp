#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <string.h>

const int BAUD = 9600;
const char* ssid = "";
const char* password = "";

const int WOL_PORT = 9;

MDNSResponder mdns;
WiFiUDP udp;

void setupWifi();
unsigned char* createPacket(const char* address);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

	Serial.begin(BAUD);
	Serial.println("subteno system initializing");
        setupWifi();

        digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
        unsigned char* packet;

        packet = createPacket("1C:6F:65:9E:69:8A");

        udp.beginPacket("192.168.1.100", WOL_PORT);
        for(int i = 0; i < 102; i++)
                udp.write(packet[i]);
        udp.endPacket();

	delay(10000);
        Serial.println("waking");
}

void setupWifi()
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

        if (mdns.begin("esp8266", WiFi.localIP()))
                Serial.println("ok");
        else
        {
                Serial.println("failed.");
                while(1){delay(1000);}
        }

		Serial.print("Acquired IP: ");
        Serial.println(WiFi.localIP());
}

unsigned char* createPacket(const char* address)
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