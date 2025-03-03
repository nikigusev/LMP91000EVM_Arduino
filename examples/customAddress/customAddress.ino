#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// Create the sensor object using SENSOR_H2S_FIGARO.
// Although we can’t change the LMP91000 I2C address (it's fixed at 0x48),
// we simulate a custom address scenario by specifying a configuration pin.
ElectrochemicalGasSensor sensor(SENSOR_H2S_FIGARO, A0, 5);

void setup() {
  Serial.begin(115200);
  if (!sensor.begin()) {
    Serial.println("ERROR: Can't init the sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("Sensor (Figaro H2S) initialized with custom configuration pin!");
}

void loop() {
  double reading = sensor.getPPM();
  Serial.print("Sensor reading: ");
  Serial.print(reading, 5);
  Serial.println(" PPM");
  delay(2500);
}
