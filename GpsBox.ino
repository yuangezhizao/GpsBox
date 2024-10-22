static const uint32_t USB_baud = 115200;
static const uint16_t GPS_baud = 9600;
static const uint16_t print_interval = 2000;
static uint64_t current_millis = 0;
static uint64_t previous_millis = 0;

void setup() {
  Serial.begin(USB_baud);
  Serial0.begin(GPS_baud);

  Serial.println("[" + String(millis()) + "] Setup() end, start loop()...");
}

void loop() {
  while (Serial0.available() > 0) {
    Serial.write(Serial0.read());
  }

  // DO NOT WRITE CODE AFTER HERE
  current_millis = millis();
  if (current_millis - previous_millis >= print_interval) {
    previous_millis = current_millis;
    Serial.println("[" + String(millis()) + "] Waiting for the gps_serial, please check...");
  }
}
