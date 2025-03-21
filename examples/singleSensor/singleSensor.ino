#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// Use the SGX H2S sensor configuration on analog pin A0 (no config pin used)
ElectrochemicalGasSensor sensor(SENSOR_H2S_SGX, A0, -1);

void setup() {
  Serial.begin(115200);
  if (!sensor.begin()) {
    Serial.println("ERROR: Can't init the sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("H2S sensor (SGX PS4-H2S-100) initialized successfully!");
}

void loop() {
  double reading = sensor.getPPM();
  Serial.print("Sensor reading: ");
  Serial.print(reading, 5);
  Serial.println(" PPM");
  delay(2500);
}
