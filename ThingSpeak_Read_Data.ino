#include "ThingSpeak.h"
#include <WiFi.h>
#include <Wire.h>
#define WLAN_SSID       "TechAmplifiers"
#define WLAN_PASS       "123456789"

int statusCode = 0;
WiFiClient  client;

//---------Channel Details---------//
unsigned long counterChannelNumber = 8***3;            // Channel ID
const char * myCounterReadAPIKey = "4C55BZ*******DB3W"; // Read API Key
const int FieldNumber1 = 1;
const int FieldNumber2 = 2;
//-------------------------------//

void setup()
{
  //WiFi.mode(WIFI_STA);

  Serial.begin(115200);
  delay(10);
  Serial.println(F("Thingspeak Read demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
  delay(1000);
}

void loop()
{
  long temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.println("Temperature:");
    Serial.println(temp);
    Serial.println("*C");
  }
  else
  {
    Serial.println("Unable to read");
    Serial.println("or No internet!");
  }
  delay(100);
}
