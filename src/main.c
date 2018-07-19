#include <Arduino.h>
#include <string.h>

const int BAUD = 9600;
const char* ssid = "ssid";
const char* password = "key";

MDNSResponder mdns;

void setupWifi();

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(BAUD);
	Serial.println("subteno system initializing");
}

void loop()
{
	delay(1000);
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