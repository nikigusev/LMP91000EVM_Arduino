#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// Define a calibration offset (adjust this based on your test environment)
const double internalZeroCalibration = 0.078;

// Create a custom sensor configuration based on the CO sensor
// (This is just an example – the values here come from the original example)
const sensorType SENSOR_CO_CALIBRATED = {
    70.0F,                    // nanoAmperesPerPPM
    internalZeroCalibration,  // internalZeroCalibration
    ADS_GAIN_4_096V,          // adsGain (legacy; not used with analogRead)
    TIA_GAIN_350_KOHM,        // TIA gain
    RLOAD_10_OHM,             // Load resistor
    REF_EXTERNAL,             // External reference (2.5V)
    INTERNAL_ZERO_20_PERCENT, // Internal zero: 20% of VREF
    BIAS_SIGN_NEGATIVE,       // Negative bias
    BIAS_0_PERCENT,           // 0% bias
    FET_SHORT_DISABLED,       // FET short disabled
    OP_MODE_3LEAD_AMP_CELL    // 3-lead amperometric cell mode
};

// For the new library, the constructor takes (sensorType, analog input pin, config pin)
// Here we use analog pin A0 for VOUT and digital pin 32 for configuration control.
ElectrochemicalGasSensor sensor(SENSOR_CO_CALIBRATED, A0, 32);

void setup() {
  Serial.begin(115200);
  // Initialize the sensor
  if (!sensor.begin()) {
    Serial.println("ERROR: Can't init the sensor! Check connections!");
    while (true)
      delay(100);
  }
  Serial.println("Sensor initialized successfully!");
}

void loop() {
  // Read the gas concentration in PPM
  double reading = sensor.getPPM();
  Serial.print("Sensor reading: ");
  Serial.print(reading, 5);
  Serial.println(" PPM");
  delay(2500);
}
