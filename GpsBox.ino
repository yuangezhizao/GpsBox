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

void print_GPS_data(TinyGPSPlus& gps) {
  char hdop_str[16];
  char satellites_str[16];

  char time_str[20];
  char date_str[20];
  char location_str[30];
  char location_age_str[16];
  char altitude_str[16];
  char course_str[16];
  char speed_str[16];

  if (gps.hdop.isValid()) {
    sprintf(hdop_str, "HDOP: %.f", gps.hdop.hdop());
  } else {
    sprintf(hdop_str, "HDOP: -");
  }

  if (gps.satellites.isValid()) {
    sprintf(satellites_str, "Sat: %d", gps.satellites.value());
  } else {
    sprintf(satellites_str, "Sat: *");
  }

  if (gps.time.isValid()) {  //TODO: bypass 00:00:00
    // sprintf(time_str, "Time: %02d:%02d:%02d.%02d",
    //         gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond());
    sprintf(time_str, " %02d:%02d:%02d",
            gps.time.hour(), gps.time.minute(), gps.time.second());
  } else {
    sprintf(time_str, "INV");
  }

  if (gps.date.isValid()) {
    sprintf(date_str, "D/T: %02d/%02d/%02d",
            gps.date.year(), gps.date.month(), gps.date.day());
  } else {
    sprintf(date_str, "D/T: INV");
  }

  if (gps.location.isValid()) {
    sprintf(location_str, "Loc: %.6f %.6f", gps.location.lat(), gps.location.lng());
    sprintf(location_age_str, "Age: %d", gps.location.age());
  } else {
    sprintf(location_str, "Loc: INV");
    sprintf(location_age_str, "Age: INV");
  }

  if (gps.altitude.isValid()) {
    sprintf(altitude_str, "Alt: %.2f", gps.altitude.meters());
  } else {
    sprintf(altitude_str, "Alt: INV");
  }

  if (gps.course.isValid()) {
    sprintf(course_str, "Cou: %.2f", gps.course.deg());
  } else {
    sprintf(course_str, "Cou: INV");
  }

  if (gps.speed.isValid()) {
    // sprintf(speed_str, "%.2f km/h", gps.speed.kmph());
    sprintf(speed_str, "%.2f", gps.speed.kmph());
  } else {
    sprintf(speed_str, "Spd: INV");
  }

  print_to_serial(hdop_str, satellites_str, time_str, date_str, location_str, location_age_str, altitude_str, course_str, speed_str);
}

void print_to_serial(const char* hdop_str, const char* satellites_str, const char* time_str, const char* date_str, const char* location_str, const char* location_age_str, const char* altitude_str, const char* course_str, const char* speed_str) {
  Serial.println("\n");
  Serial.println(hdop_str);
  Serial.println(satellites_str);
  Serial.print(date_str);
  Serial.println(time_str);
  Serial.println(location_str);
  Serial.println(location_age_str);
  Serial.println(altitude_str);
  Serial.println(course_str);
  Serial.println(speed_str);
}

void loop() {
  while (Serial0.available() > 0) {
    // Serial.write(Serial0.read());

    gps_serial = Serial0.read();
    Serial.print(gps_serial);

    if (gps.encode(gps_serial)) {
      print_GPS_data(gps);
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
