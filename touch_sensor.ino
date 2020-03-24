#include <CapacitiveSensor.h>
CapacitiveSensor touch_sensor = CapacitiveSensor(D4, D5);
bool touched = false;

void setupTouchSensor() {
  touch_sensor.set_CS_Timeout_Millis(100);
}

bool isTouched() {
  bool s = touch_sensor.capacitiveSensor(100) > 0;
  if (touched == true && s == false) {
    touched = false;
    Serial.println("Finger Untouched!");
    return true;
  } else if (touched == true && s == true) {
    // finger still down
    return false;
  } else if (touched == false && s == true) {
    Serial.println("Finger applied!");
    touched = true;
    return false;
  } else if (touched == false && s == false) {
    // finger still up
    return false;
  }
}
