#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

char ssid[32] = "";
char password[32] = "";

const char compile_date[] = __DATE__ " " __TIME__;

#define LED_COUNT 5
#define LED_PIN D6

int wait = 0;
int faderate = 40000;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB);

void setup() {
  setupSerial();
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()  {
  sunrise();
  sunset();
}

void setupSerial() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.printf("ESP8266 Chip id = %08X\n", ESP.getChipId());
  Serial.printf("Sketch compiled %s\n", compile_date);
  wifiSetup();
}
