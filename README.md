# LMP91000EVM_Arduino

**LMP91000EVM_Arduino** is an Arduino library for interfacing with the Texas Instruments LMP91000EVM evaluation module using electrochemical gas sensors. This library is an adaptation of the original Soldered Arduino library for the LMP91000 Sensor AFE. It has been modified to use Arduino's built-in `analogRead()` for sampling the LMP91000’s VOUT signal instead of an external ADC (like the ADS1015).

The library supports multiple electrochemical sensors by using configurable sensor parameters defined in `sensorConfigData.h`. Predefined sensor configurations include:

- **SENSOR_NH3** – FECS44‑100 (Ammonia Sensor)
- **SENSOR_H2S_FIGARO** – FECS50‑100 (Hydrogen Sulfide Sensor, Figaro)
- **SENSOR_H2S_SGX** – PS4‑H2S‑100 (Hydrogen Sulfide Sensor, SGX Sensortech)

> **Important:** Although your Arduino ADC may use a 5 V reference, the LMP91000’s internal reference is fixed at 2.5 V. All voltage calculations related to the sensor’s zero offset are based on 2.5 V.

## Features

- **Direct Analog Sampling:**  
  Uses `analogRead()` on the LMP91000’s VOUT pin—no external ADC is needed.

- **Configurable Sensor Parameters:**  
  Easily switch between sensor types using preconfigured definitions in `sensorConfigData.h` or create your own custom configuration.

- **Built-in Averaging Functions:**  
  Functions for averaging multiple sensor readings to reduce noise.

- **Custom Configuration Support:**  
  Runtime adjustments (e.g., TIA gain and calibration offsets) allow you to tailor the sensor response.

- **Multiple Sensor Support:**  
  Examples show how to initialize and read from one or more sensors simultaneously.

## Installation

1. **Download the Library:**  
   Clone or download this repository.

2. **Install in the Arduino IDE:**  
   Place the library folder (named `LMP91000EVM_Arduino`) into your Arduino `libraries` folder and restart the IDE.

3. **Library Folder Structure:**

   ```
   LMP91000EVM_Arduino/
   ├── library.properties
   ├── README.md
   ├── LICENSE
   ├── src/
   │   ├── ElectrochemicalGasSensor.h
   │   ├── ElectrochemicalGasSensor.cpp
   │   ├── LMP91000.h
   │   ├── LMP91000.cpp
   │   └── sensorConfigData.h
   └── examples/
       ├── calibrateSensor/
       │   └── calibrateSensor.ino
       ├── twoSensors/
       │   └── twoSensors.ino
       ├── singleSensor/
       │   └── singleSensor.ino
       ├── customConfig/
       │   └── customConfig.ino
       ├── customAddress/
       │   └── customAddress.ino
       └── averagedMeasurement/
           └── averagedMeasurement.ino
   ```

## Hardware Requirements

- **LMP91000EVM Evaluation Module:**  
  Ensure the following modifications are made:
  - Remove resistor R8 (to bypass the onboard ADC).
  - Remove resistor R7 (for proper external supply configuration).
  - Set jumpers (e.g., J_MENB, 2-WIRE) as described in the LMP91000EVM User’s Guide.
  - Wire the sensor to the sensor footprint and connect VOUT to an Arduino analog input.

- **Electrochemical Gas Sensor:**  
  Attach a supported sensor (e.g., FECS44‑100, FECS50‑100, or PS4‑H2S‑100) to the LMP91000EVM.

- **Arduino Board:**  
  The library works with any Arduino board. It uses I²C for configuring the LMP91000 and analogRead() for voltage sampling.

> **Note:** Although the Arduino’s ADC reference might be 5 V, the LMP91000’s calculations use its fixed 2.5 V reference.

## Usage

1. **Include the Library:**

   ```cpp
   #include <Wire.h>
   #include "ElectrochemicalGasSensor.h"
   #include "sensorConfigData.h"
   ```

2. **Create a Sensor Object:**

   The constructor takes the sensor type, the analog input pin for VOUT, and an optional configuration pin for controlling the LMP91000's configuration. For example:

   ```cpp
   // For the SGX PS4‑H2S‑100 sensor:
   ElectrochemicalGasSensor sensor(SENSOR_H2S_SGX, A0, -1);
   ```

3. **Initialization:**

   In `setup()`, initialize the sensor:

   ```cpp
   if (!sensor.begin()) {
     Serial.println("ERROR: Sensor initialization failed!");
     while (true);
   }
   ```

4. **Reading Sensor Data:**

   Read voltage, PPM, or PPB:

   ```cpp
   double ppm = sensor.getPPM();
   double ppb = sensor.getPPB();
   double avgPpm = sensor.getAveragedPPM(5, 1);  // Average 5 readings, 1-second interval
   ```

5. **Customization:**

   Adjust TIA gain or calibration offset at runtime:

   ```cpp
   sensor.setCustomTiaGain(300000.0);  // Set TIA gain to 300 kΩ
   ```

## Sensor Configurations
The file `sensorConfigData.h` defines the sensor-specific parameters. Predefined configurations include:

- **SENSOR_NH3:** FECS44‑100 (Ammonia Sensor)  
- **SENSOR_H2S_FIGARO:** FECS50‑100 (Hydrogen Sulfide Sensor, Figaro)  
- **SENSOR_H2S_SGX:** PS4‑H2S‑100 (Hydrogen Sulfide Sensor, SGX Sensortech)

You can modify these values or add new configurations based on your calibration data.

## Examples
The library comes with several example sketches:

- **calibrateSensor.ino:** Calibrate the sensor in a known environment (e.g., clean air) to determine a calibration offset.
- **twoSensors.ino:** Initialize and read from two sensors simultaneously.
- **singleSensor.ino:** Read from a single sensor (e.g., using the SGX PS4‑H2S‑100 configuration).
- **customConfig.ino:** Demonstrates how to define and use a custom sensor configuration.
- **customAddress.ino:** Although the LMP91000’s I²C address is fixed (0x48), this example shows how to simulate a custom address setup using configuration pins.
- **averagedMeasurement.ino:** Uses the built‑in averaging function to display an averaged gas concentration.

Each example is located in the `examples/` folder and can be opened directly from the Arduino IDE.

## Troubleshooting & Considerations
- **Sensor Response Time:**  
  Electrochemical sensors have inherent response times due to chemical reaction dynamics. Reducing delays in software may increase update rate, but physical response limits remain.

- **Calibration:**  
  Fine-tune the internal zero calibration value using the calibration example to ensure accurate sensor readings in a known baseline environment.

- **I²C Addressing:**  
  The LMP91000’s I²C address is fixed at 0x48. For multiple modules on the same bus, hardware modifications would be necessary.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements
This library is adapted from the original Soldered Arduino library for the LMP91000 Sensor AFE. Special thanks to Texas Instruments and the sensor manufacturers for providing detailed datasheets and design guidelines.

## Happy sensing!
Feel free to modify the author details, URLs, and any parameters specific to your project.