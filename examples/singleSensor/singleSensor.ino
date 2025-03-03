#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// Define the analog input pin where VOUT is connected (e.g., A0)
// Optionally, if you have a pin to control configuration (J_MENB), specify it; otherwise use -1.
#define SENSOR_ANALOG_PIN A0
#define CONFIG_PIN        -1

// Create a gas sensor object using the CO sensor configuration.
ElectrochemicalGasSensor gasSensor(SENSOR_CO, SENSOR_ANALOG_PIN, CONFIG_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor to open
  Serial.println("Initializing Gas Sensor...");
  
  if (!gasSensor.begin()) {
    Serial.println("Sensor initialization failed!");
    while (1);
  }
  Serial.println("Sensor initialized successfully.");
}

void loop() {
  // Take a measurement every second
  double ppm = gasSensor.getPPM();
  Serial.print("Gas Concentration: ");
  Serial.print(ppm, 2);
  Serial.println(" ppm");
  delay(1000);
}
