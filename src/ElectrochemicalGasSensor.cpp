#include "ElectrochemicalGasSensor.h"

ElectrochemicalGasSensor::ElectrochemicalGasSensor(sensorType _t, int _analogPin, int _configPin)
{
    analogPin = _analogPin;
    type = _t;
    configPin = _configPin;
}

bool ElectrochemicalGasSensor::begin()
{
    // Initialize I2C for LMP91000 communication
    Wire.begin();

    // Create LMP91000 object
    lmp = new LMP91000();

    // If a config pin is provided, initialize it.
    if (configPin != -1)
    {
        pinMode(configPin, OUTPUT);
        digitalWrite(configPin, HIGH); // disable LMP configuration initially
    }

    // Configure the LMP91000 sensor front-end.
    bool result = configureLMP();

    return result;
}

bool ElectrochemicalGasSensor::configureLMP()
{
    if (configPin != -1)
        digitalWrite(configPin, LOW);

    // Build register values according to the sensor configuration
    uint8_t tiacn = 0x00;
    tiacn |= (type.TIA_GAIN_IN_KOHMS << 2);
    tiacn |= type.RLOAD;

    uint8_t refcn = 0x00;
    refcn |= (type.REF_SOURCE << 7);
    refcn |= (type.INTERNAL_ZERO << 5);
    refcn |= (type.BIAS_SIGN << 4);
    refcn |= type.BIAS;

    uint8_t modecn = 0x00;
    modecn |= (type.FET_SHORT << 7);
    modecn |= type.OP_MODE;

    uint8_t res = lmp->configure(tiacn, refcn, modecn);

    // Save key variables for later use in calculations.
    tiaGainInKOHms = getTiaGain();
    internalZeroPercent = getInternalZeroPercent();

    if (configPin != -1)
        digitalWrite(configPin, HIGH);

    return res;
}

double ElectrochemicalGasSensor::getVoltage()
{
    // Read the raw analog value and convert it to voltage.
    int rawReading = analogRead(analogPin);
    double voltage = (rawReading / 1023.0) * ANALOG_REF_VOLTAGE;
    return voltage;
}

double ElectrochemicalGasSensor::getPPM()
{
    double voltage = getVoltage();

    #ifdef ELECTROCHEMICAL_SENSOR_DEBUG
    Serial.println();
    Serial.println("Electrochemical gas sensor readings:");
    Serial.print("Raw voltage measurement: ");
    Serial.print(voltage, 10);
    Serial.println(" V");
    #endif

    // Remove the reference voltage offset.
    // Since the LMP91000 VREF is fixed at 2.5V, we subtract 2.5V * (internalZeroPercent/100)
    double voltsNoRef = voltage - (2.5 * (internalZeroPercent / 100.0F));

    #ifdef ELECTROCHEMICAL_SENSOR_DEBUG
    Serial.print("Voltage without reference value: ");
    Serial.print(voltsNoRef, 10);
    Serial.println(" V");
    #endif

    // Apply any calibration offset
    voltsNoRef += type.internalZeroCalibration;

    #ifdef ELECTROCHEMICAL_SENSOR_DEBUG
    Serial.print("Voltage after calibration: ");
    Serial.print(voltsNoRef, 10);
    Serial.println(" V");
    Serial.println("");
    #endif

    // Calculate the sensor current (I = V / (TIA gain in ohms))
    double current = voltsNoRef / (tiaGainInKOHms * 1000);
    // Convert current to ppm using the sensor’s sensitivity (nanoamperes per ppm)
    double ppm = current / (type.nanoAmperesPerPPM * 1e-9);

    // In case of noise causing slight negative readings, round up to zero.
    if (ppm < 0)
        ppm = 0;
    return ppm;
}

double ElectrochemicalGasSensor::getPPB()
{
    return getPPM() * 1000.0;
}

double ElectrochemicalGasSensor::getAveragedPPM(uint8_t _numMeasurements, uint8_t _secondsDelay)
{
    double totalMeasurements = 0;
    for (int i = 0; i < _numMeasurements; i++)
    {
        totalMeasurements += getPPM();
        delay(1000 * _secondsDelay);
    }
    return totalMeasurements / _numMeasurements;
}

double ElectrochemicalGasSensor::getAveragedPPB(uint8_t _numMeasurements, uint8_t _secondsDelay)
{
    return getAveragedPPM(_numMeasurements, _secondsDelay) * 1000;
}

float ElectrochemicalGasSensor::getTiaGain()
{
    switch (type.TIA_GAIN_IN_KOHMS)
    {
    case TIA_GAIN_EXTERNAL:
        return -1;
    case TIA_GAIN_2_75_KOHM:
        return 2750.00F;
    case TIA_GAIN_3_5_KOHM:
        return 3500.00F;
    case TIA_GAIN_7_KOHM:
        return 7000.00F;
    case TIA_GAIN_14_KOHM:
        return 14000.00F;
    case TIA_GAIN_35_KOHM:
        return 35000.00F;
    case TIA_GAIN_120_KOHM:
        return 120000.00F;
    case TIA_GAIN_350_KOHM:
        return 350000.00F;
    default:
        return -1;
    }
}

void ElectrochemicalGasSensor::setCustomTiaGain(float _tiaGain)
{
    tiaGainInKOHms = _tiaGain;
}

float ElectrochemicalGasSensor::getInternalZeroPercent()
{
    switch (type.INTERNAL_ZERO)
    {
    case INTERNAL_ZERO_20_PERCENT:
        return 20.00F;
    case INTERNAL_ZERO_50_PERCENT:
        return 50.00F;
    case INTERNAL_ZERO_67_PERCENT:
        return 67.00F;
    case INTERNAL_ZERO_BYPASSED:
        return -1;
    default:
        return -1;
    }
}
