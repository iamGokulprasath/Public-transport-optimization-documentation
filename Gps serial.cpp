#include <TinyGPS.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(8, 9); // RX, TX pins for GPS module
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      float lat, lon;
      unsigned long age;
      gps.f_get_position(&lat, &lon, &age);

      if (age < 1000) { // Consider data valid if age < 1000 milliseconds
        Serial.print("Latitude: ");
        Serial.println(lat, 6); // Print latitude with 6 decimal places
        Serial.print("Longitude: ");
        Serial.println(lon, 6); // Print longitude with 6 decimal places

        // Send this data to a cloud platform or server for further processing
        // You can use MQTT, HTTP, or other protocols to transmit the data
      }
    }
  }
}
