#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

#define NUM_READINGS 5
#define SECS_BETWEEN_READINGS 3

// Use the FECS44-100 ammonia sensor configuration on analog pin A0.
ElectrochemicalGasSensor sensor(SENSOR_NH3, A0, -1);

void setup() {
  Serial.begin(115200);
  if (!sensor.begin()) {
    Serial.println("ERROR: Can't init the sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("Sensor initialized successfully!");
}

void loop() {
  double reading = sensor.getAveragedPPM(NUM_READINGS, SECS_BETWEEN_READINGS);
  Serial.print("Averaged sensor reading: ");
  Serial.print(reading, 5);
  Serial.println(" PPM");
  delay(2500);
}
