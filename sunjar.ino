#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

char ssid[32] = "";
char password[32] = "";

const char compile_date[] = __DATE__ " " __TIME__;


void setup() {
setupSerial();
}

void loop() {
  // put your main code here, to run repeatedly:

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
