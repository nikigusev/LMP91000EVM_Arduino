#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// SENSOR_NH3 for ammonia on analog pin A0
ElectrochemicalGasSensor sensorNH3(SENSOR_NH3, A0, 25);
// SENSOR_H2S_FIGARO for H₂S (Figaro) on analog pin A1
ElectrochemicalGasSensor sensorH2S(SENSOR_H2S_FIGARO, A1, 32);

void setup() {
  Serial.begin(115200);
  if (!sensorNH3.begin()) {
    Serial.println("ERROR: Can't init the NH3 sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("Ammonia sensor initialized successfully!");
  
  if (!sensorH2S.begin()) {
    Serial.println("ERROR: Can't init the H2S sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("H2S sensor (Figaro) initialized successfully!");
}

void loop() {
  double nh3Reading = sensorNH3.getPPM();
  double h2sReading = sensorH2S.getPPM();
  
  Serial.print("Ammonia (NH3): ");
  Serial.print(nh3Reading, 5);
  Serial.print(" PPM,  H2S (Figaro): ");
  Serial.print(h2sReading, 5);
  Serial.println(" PPM");
  
  delay(2500);
}
