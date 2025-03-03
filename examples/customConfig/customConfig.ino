#include <Wire.h>
#include "ElectrochemicalGasSensor.h"
#include "sensorConfigData.h"

// Define a custom sensor configuration based on the SGX H2S sensor,
// but with a different TIA gain and calibration (adjust values as needed).
const sensorType SENSOR_CUSTOM = {
    90.0F,                    // nanoAmperesPerPPM (same sensitivity as SGX H2S)
    0.0,                      // internalZeroCalibration (set after calibration)
    ADS_GAIN_4_096V,          // adsGain (legacy parameter; not used with analogRead)
    TIA_GAIN_120_KOHM,        // custom TIA gain (e.g., 120 kΩ instead of 350 kΩ)
    RLOAD_100_OHM,            // Load resistor (100 Ω recommended for SGX)
    REF_EXTERNAL,             // External reference (2.5V)
    INTERNAL_ZERO_20_PERCENT, // Internal zero set to 20%
    BIAS_SIGN_NEGATIVE,       // Negative bias
    BIAS_0_PERCENT,           // 0% bias
    FET_SHORT_DISABLED,       // FET short disabled
    OP_MODE_3LEAD_AMP_CELL    // 3-lead amperometric cell mode
};

// Create the sensor object using the custom configuration,
// with analog pin A0 for VOUT.
ElectrochemicalGasSensor sensor(SENSOR_CUSTOM, A0, -1);

void setup() {
  Serial.begin(115200);
  if (!sensor.begin()) {
    Serial.println("ERROR: Can't init the sensor! Check connections!");
    while (true) delay(100);
  }
  Serial.println("Sensor initialized with custom configuration!");
}

void loop() {
  double reading = sensor.getPPM();
  Serial.print("Custom sensor reading: ");
  Serial.print(reading, 5);
  Serial.println(" PPM");
  delay(2500);
}
