#ifndef __ELECTROCHEMICAL_GAS_SENSOR_SOLDERED__
#define __ELECTROCHEMICAL_GAS_SENSOR_SOLDERED__

#include "Arduino.h"
#include "LMP91000.h"
#include "sensorConfigData.h"

#define ANALOG_REF_VOLTAGE 5.0F   // Change this if your analog reference is different

class ElectrochemicalGasSensor
{
  public:
    // Modified constructor: now takes sensor type, the analog input pin for VOUT, and an optional config pin.
    ElectrochemicalGasSensor(sensorType _t, int _analogPin, int _configPin = -1);
    bool begin();
    bool configureLMP();
    double getVoltage();
    double getPPM();
    double getPPB();
    double getAveragedPPM(uint8_t _numMeasurements = 5, uint8_t _secondsDelay = 2);
    double getAveragedPPB(uint8_t _numMeasurements = 5, uint8_t _secondsDelay = 2);
    void setCustomTiaGain(float _tiaGain);

  private:
    LMP91000 *lmp;
    int analogPin;
    int configPin;
    sensorType type;
    float tiaGainInKOHms;
    float internalZeroPercent;
    float getTiaGain();
    float getInternalZeroPercent();
};

#endif
