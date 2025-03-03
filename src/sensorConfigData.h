#ifndef __ELECTROCHEMICAL_GAS_SENSOR_CONFIG_DATA_SOLDERED__
#define __ELECTROCHEMICAL_GAS_SENSOR_CONFIG_DATA_SOLDERED__

// --- Definitions for configuring the analog front-end ---
// TIA gain settings (the value here is a code that will be shifted in the TIACN register)
#define TIA_GAIN_EXTERNAL  0x00
#define TIA_GAIN_2_75_KOHM 0x01
#define TIA_GAIN_3_5_KOHM  0x02
#define TIA_GAIN_7_KOHM    0x03
#define TIA_GAIN_14_KOHM   0x04
#define TIA_GAIN_35_KOHM   0x05
#define TIA_GAIN_120_KOHM  0x06
#define TIA_GAIN_350_KOHM  0x07

// RLOAD values: these select the load resistor on the LMP91000
#define RLOAD_10_OHM  0x00
#define RLOAD_33_OHM  0x01
#define RLOAD_50_OHM  0x02
#define RLOAD_100_OHM 0x03

// Reference source: internal or external reference voltage
#define REF_INTERNAL 0x00
#define REF_EXTERNAL 0x01

// Internal zero voltage setting (the percentage of VREF that defines the LMP91000’s zero)
#define INTERNAL_ZERO_20_PERCENT 0x00
#define INTERNAL_ZERO_50_PERCENT 0x01
#define INTERNAL_ZERO_67_PERCENT 0x02
#define INTERNAL_ZERO_BYPASSED   0x03

// Bias sign (determines the polarity of the bias voltage)
#define BIAS_SIGN_NEGATIVE 0x00
#define BIAS_SIGN_POSITIVE 0x01

// Bias percentages (setting the bias level in percent of VREF)
#define BIAS_0_PERCENT  0x00
#define BIAS_1_PERCENT  0x01
#define BIAS_2_PERCENT  0x02
#define BIAS_4_PERCENT  0x03
#define BIAS_6_PERCENT  0x04
#define BIAS_8_PERCENT  0x05
#define BIAS_10_PERCENT 0x06
#define BIAS_12_PERCENT 0x07
#define BIAS_14_PERCENT 0x08
#define BIAS_16_PERCENT 0x09
#define BIAS_18_PERCENT 0x0A
#define BIAS_20_PERCENT 0x0B
#define BIAS_22_PERCENT 0x0C
#define BIAS_24_PERCENT 0x0D

// FET short settings (to bypass the sensor when off)
#define FET_SHORT_DISABLED 0x00
#define FET_SHORT_ENABLED  0x01

// Operation mode settings for the LMP91000
#define OP_MODE_DEEP_SLEEP          0x00
#define OP_MODE_2LEAD_GROUND_CELL   0x01
#define OP_MODE_STANDBY             0x02
#define OP_MODE_3LEAD_AMP_CELL      0x03
#define OP_MODE_TEMPERATURE_TIA_OFF 0x06
#define OP_MODE_TEMPERATURE_TIA_ON  0x07

// --- ADS Gain Settings (retained for compatibility, even though analogRead() is now used) ---
#define ADS_GAIN_6_144V 0x0000
#define ADS_GAIN_4_096V 0x0200
#define ADS_GAIN_2_048V 0x0400
#define ADS_GAIN_1_024V 0x0600
#define ADS_GAIN_0_512V 0x0800
#define ADS_GAIN_0_256V 0x0A00

// --- Sensor configuration structure ---
struct sensorType
{
    double nanoAmperesPerPPM;       // Sensitivity (nA per ppm of target gas)
    double internalZeroCalibration; // Calibration offset (determined empirically)
    uint16_t adsGain;               // ADC gain (for legacy configuration; not used in direct analogRead)
    uint8_t TIA_GAIN_IN_KOHMS;      // TIA gain setting (in KΩ)
    uint8_t RLOAD;                  // Load resistor setting
    uint8_t REF_SOURCE;             // Reference voltage source
    uint8_t INTERNAL_ZERO;          // Internal zero voltage setting
    uint8_t BIAS_SIGN;              // Bias polarity
    uint8_t BIAS;                   // Bias percentage
    uint8_t FET_SHORT;              // FET short configuration
    uint8_t OP_MODE;                // Operating mode (e.g., 3-lead amperometric cell)
};

// -----------------------------------------------------------------------------
// Custom sensor configurations

// 1. SENSOR_NH3 (FECS44-100)
//    - Ammonia sensor with ~100 nA/ppm sensitivity and a recommended load resistor of 33Ω.
const sensorType SENSOR_NH3 = {
    100.0F,                   // nanoAmperesPerPPM: 100 ± 30 nA/ppm
    0.0,                      // internalZeroCalibration: Adjust based on calibration
    ADS_GAIN_4_096V,          // adsGain: Using 4.096V range
    TIA_GAIN_35_KOHM,         // TIA_GAIN_IN_KOHMS: 35 KΩ chosen to yield moderate voltage levels
    RLOAD_33_OHM,             // RLOAD: 33 Ω as recommended
    REF_EXTERNAL,             // REF_SOURCE: External reference (2.5V)
    INTERNAL_ZERO_20_PERCENT, // INTERNAL_ZERO: 20% of VREF
    BIAS_SIGN_NEGATIVE,       // BIAS_SIGN: Negative bias (default for many sensors)
    BIAS_0_PERCENT,           // BIAS: 0% (no additional bias required)
    FET_SHORT_DISABLED,       // FET_SHORT: Disabled
    OP_MODE_3LEAD_AMP_CELL    // OP_MODE: 3-lead amperometric cell mode
};

// 2. SENSOR_H2S_FIGARO (FECS50-100)
//    - Hydrogen sulfide sensor (Figaro) with ~700 nA/ppm sensitivity and a recommended load resistor of 10Ω.
const sensorType SENSOR_H2S_FIGARO = {
    700.0F,                   // nanoAmperesPerPPM: 700 ± 150 nA/ppm
    0.0,                      // internalZeroCalibration: Adjust based on calibration
    ADS_GAIN_4_096V,          // adsGain: Using 4.096V range
    TIA_GAIN_7_KOHM,          // TIA_GAIN_IN_KOHMS: 7 KΩ chosen for higher current output
    RLOAD_10_OHM,             // RLOAD: 10 Ω as recommended
    REF_EXTERNAL,             // REF_SOURCE: External reference
    INTERNAL_ZERO_20_PERCENT, // INTERNAL_ZERO: 20% of VREF
    BIAS_SIGN_NEGATIVE,       // BIAS_SIGN: Negative
    BIAS_0_PERCENT,           // BIAS: 0% bias
    FET_SHORT_DISABLED,       // FET_SHORT: Disabled
    OP_MODE_3LEAD_AMP_CELL    // OP_MODE: 3-lead amperometric cell mode
};

// 3. SENSOR_H2S_SGX (PS4-H2S-100)
//    - Hydrogen sulfide sensor (SGX Sensortech) with ~90 nA/ppm sensitivity.
//      Recommended load resistor is 100Ω. Although a higher TIA gain (e.g., 350 KΩ)
//      can be used to maximize signal, you may adjust this based on your dynamic range needs.
const sensorType SENSOR_H2S_SGX = {
    90.0F,                    // nanoAmperesPerPPM: 90 ± 20 nA/ppm
    0.0,                      // internalZeroCalibration: Adjust after calibration if needed
    ADS_GAIN_4_096V,          // adsGain: Using 4.096V range
    TIA_GAIN_350_KOHM,        // TIA_GAIN_IN_KOHMS: 350 KΩ for higher sensitivity signal amplification
    RLOAD_100_OHM,            // RLOAD: 100 Ω as recommended by the datasheet
    REF_EXTERNAL,             // REF_SOURCE: External reference voltage
    INTERNAL_ZERO_20_PERCENT, // INTERNAL_ZERO: 20% of VREF
    BIAS_SIGN_NEGATIVE,       // BIAS_SIGN: Negative bias (default)
    BIAS_0_PERCENT,           // BIAS: 0% bias (not required)
    FET_SHORT_DISABLED,       // FET_SHORT: Disabled
    OP_MODE_3LEAD_AMP_CELL    // OP_MODE: 3-lead amperometric cell mode
};

#endif
