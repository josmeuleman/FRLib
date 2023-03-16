// Testscript OverSampling & Timers on the Flight Recorder PCB
// Required hardware:
// - 1x potmeter
// - 6x breadboard cables female-male
// Connections:
// - Potmeter1, GND - Analog Input J6, GND
// - Potmeter1, Wiper - Analog Input J6, D35
// - Potmeter1, VCC - Analog Input J6, 3.3V
// Required libraries:
// - FRLib (download from https://github.com/josmeuleman/FRLib, unzipped in ../Documents/Arduino/libraries/ )
//
// 2023-03-14, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include <FRGeneric.h>

HardwareSerial SerialGPS(2);  // The serial connection to the GPS device
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);     // Start the serial communciation
  SerialGPS.begin(9600);
}

void loop() {
  long tMillis = millis();

  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }
  Serial.printf("The time since startup in milliseconds: %d; ", tMillis);
  Serial.printf("The time of the GPS sensor: %s",createTimeString(gps.time.hour(), gps.time.minute(), gps.time.second()));
  
  Serial.println();
  delay(1000);

}