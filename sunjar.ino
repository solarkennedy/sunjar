#define FASTLED_ALLOW_INTERRUPTS 0
#define POWER_DEBUG_PRINT 1
#define FASTLED_INTERRUPT_RETRY_COUNT 1

#include <FastLED.h>
FASTLED_USING_NAMESPACE

int wait = 0;
int faderate = 40000;

#define DATA_PIN            6
#define NUM_LEDS            5
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         RGB

CRGB leds[NUM_LEDS];

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

CRGBPalette16 gPal;


void setup() {
  setupSerial();
  setupStrip();
  // setupWifi();
}


void loop()  {
  softtwinkles();
  FastLED.show();
  FastLED.delay(1000 / 60);
  //EVERY_N_MILLISECONDS( 20 ) {
  //  gHue++;  // slowly cycle the "base color" through the rainbow
 // }
}

void setupSerial() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();
  const char compile_date[] = __DATE__ " " __TIME__;
  Serial.printf("ESP8266 Chip id = %08X\n", ESP.getChipId());
  Serial.printf("Sketch compiled %s\n", compile_date);
}

void setupStrip() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
  .setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
}
