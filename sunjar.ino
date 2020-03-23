#define FASTLED_ALLOW_INTERRUPTS 0
#define POWER_DEBUG_PRINT 1
#define FASTLED_INTERRUPT_RETRY_COUNT 1


#define COOLING  20           // defines the level at which the lighting effect fades before a new "flame" generates
#define SPARKING 20


#include <FastLED.h>
FASTLED_USING_NAMESPACE

int wait = 0;
int faderate = 40000;

#define DATA_PIN            D6
#define NUM_LEDS            5
#define MAX_POWER_MILLIAMPS 50000
#define LED_TYPE            WS2812B
#define COLOR_ORDER         RGB

CRGB leds[NUM_LEDS];

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

CRGBPalette16 gPal;

long latitude = 37.7749;
long longitude = -122.4194;
String sunrise;
String sunset;
//String twilight;


double daylen, civlen;
double rise, set, twilight;
int rs;
String string_rise, string_set, string_twilight;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setupSerial();
  setupStrip();
  setupWifi();
  syncTimeFromWifi();
  digitalWrite(LED_BUILTIN, HIGH);
}

void figureOutWhatToShow() {
  int brightness;
  int h = getHour();
  int wakeup_hour = getWakeupHour();
  
  if (h >= 0 && h < wakeup_hour) {
    FastLED.setBrightness(0);
  } else if (h >= wakeup_hour && h < wakeup_hour + 1) {
    brightness = map(getMinuteOfTheHour(), 0, 59, 0, 255);
    FastLED.setBrightness(brightness);
    pacifica_loop();
  } else if (h >= wakeup_hour + 1 && h < 21) {
    FastLED.setBrightness(255);
    confetti();
  } else if (h >= 21 && h < 22) {
    brightness = map(getMinuteOfTheHour(), 0, 59, 255, 0);
    FastLED.setBrightness(brightness);
    pacifica_loop();
  } else {
    FastLED.setBrightness(0);
  }
}

void loop()  {
  figureOutWhatToShow();
  FastLED.show();
  FastLED.delay(1000 / 60);
  wifiEvents();
  EVERY_N_SECONDS( 30 ) {
    Serial.println(getCurrentTime());
    sunRiseSet();
  }
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



void sunRiseSet () {
  Serial.println("xxxxxxxxxxxxxxxxxxxx");
  Serial.println(longitude);
  Serial.println(latitude);

  daylen = __daylen__(getYear(), getMonth(), getDay(), longitude, latitude, -35.0 / 60.0, 1);
  civlen = __daylen__(getYear(), getMonth(), getDay(), longitude, latitude, -6.0, 0);
  rs = __sunriset__(getYear(), getMonth(), getDay(), longitude, latitude, -35.0 / 60.0, 1,  &rise, &set );
  //rise = rise + (config.timeZone / 10);
  //set = set + (config.timeZone / 10);
  /*
    if (config.isDayLightSaving && summerTime(absoluteActualTime)) {
    rise += 1;
    set += 1;
    }
  */
  string_rise = string_rs (rise);
  string_set = string_rs (set);
  twilight = (civlen - daylen) / 2.0;
  string_twilight = string_rs (twilight);

  Serial.println("--------------");
  Serial.println(string_rise);
  Serial.println(string_set);
  Serial.println(string_twilight);
}
