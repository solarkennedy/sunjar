
void sunrise() {
  //start out off, fade up to first color orange (255, 80, 0)
  for (int i = 0; i < faderate; i++)
  {
    int g = map(i, 0, faderate, 0, 255);
    int r = map(i, 0, faderate, 0, 128);
    colorWipe (strip.Color(r, g, 0), 0);
    strip.show();
    delay (wait);
    wifiEvents();
  }
  delay (10000);
  colorWipe(strip.Color(0, 0, 0), 0);
}

void sunset() {
  //start out off, fade up to first color orange (255, 80, 0)
  for (int i = faderate; i > 0; i--)
  {
    int g = map(i, 0, faderate, 0, 255);
    int r = map(i, 0, faderate, 0, 128);
    colorWipe (strip.Color(r, g, 0), 0);
    strip.show();
    delay(wait);

  }
  delay (10000);
  colorWipe(strip.Color(0, 0, 0), 0);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    wifiEvents();
  }
}
