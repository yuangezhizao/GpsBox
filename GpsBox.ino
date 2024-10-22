#include <TinyGPSPlus.h>

static const uint32_t USB_baud = 115200;
static const uint16_t GPS_baud = 9600;
static const uint16_t print_interval = 2000;
// static uint64_t current_millis = 0;
// static uint64_t previous_millis = 0;
char gps_serial;

TinyGPSPlus gps;

void setup() {
  Serial.begin(USB_baud);
  Serial0.begin(GPS_baud);

  Serial.println("[" + String(millis()) + "] Setup() end, start loop()...");
}

void loop() {
  while (Serial0.available() > 0) {
    // Serial.write(Serial0.read());

    gps_serial = Serial0.read();
    Serial.print(gps_serial);

    if (gps.encode(gps_serial)) {
      // Serial.println();
      // Serial.println("[" + String(millis()) + "] DEBUG charsProcessed: " + String(gps.charsProcessed()));
      // Serial.println("[" + String(millis()) + "] DEBUG sentencesWithFix: " + String(gps.sentencesWithFix()));
      // Serial.println("[" + String(millis()) + "] DEBUG failedChecksum: " + String(gps.failedChecksum()));
    } else {
      // TODO: FIX PRINT OVERFLOW HERE
      // Serial.println("[" + String(millis()) + "] Waitng for enough char...");
    }
  }

  // DO NOT WRITE CODE AFTER HERE
  // TODO: FIX PRINT LOGIC HERE
  // current_millis = millis();
  // if (current_millis - previous_millis >= print_interval) {
  //   previous_millis = current_millis;
  //   Serial.println("[" + String(millis()) + "] Waiting for the gps_serial, please check...");
  // }
}
