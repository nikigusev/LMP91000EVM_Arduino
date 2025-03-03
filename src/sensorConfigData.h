#ifndef __ELECTROCHEMICAL_GAS_SENSOR_CONFIG_DATA_SOLDERED__
#define __ELECTROCHEMICAL_GAS_SENSOR_CONFIG_DATA_SOLDERED__

// Analog front-end configuration definitions
#define TIA_GAIN_EXTERNAL  0x00
#define TIA_GAIN_2_75_KOHM 0x01
#define TIA_GAIN_3_5_KOHM  0x02
#define TIA_GAIN_7_KOHM    0x03
#define TIA_GAIN_14_KOHM   0x04
#define TIA_GAIN_35_KOHM   0x05
#define TIA_GAIN_120_KOHM  0x06
#define TIA_GAIN_350_KOHM  0x07

#define RLOAD_10_OHM  0x00
#define RLOAD_33_OHM  0x01
#define RLOAD_50_OHM  0x02
#define RLOAD_100_OHM 0x03

#define REF_INTERNAL 0x00
#define REF_EXTERNAL 0x01

#define INTERNAL_ZERO_20_PERCENT 0x00
#define INTERNAL_ZERO_50_PERCENT 0x01
#define INTERNAL_ZERO_67_PERCENT 0x02
#define INTERNAL_ZERO_BYPASSED   0x03

#define BIAS_SIGN_NEGATIVE 0x00
#define BIAS_SIGN_POSITIVE 0x01

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

#define FET_SHORT_DISABLED 0x00
#define FET_SHORT_ENABLED  0x01

#define OP_MODE_DEEP_SLEEP          0x00
#define OP_MODE_2LEAD_GROUND_CELL   0x01
#define OP_MODE_STANDBY             0x02
#define OP_MODE_3LEAD_AMP_CELL      0x03
#define OP_MODE_TEMPERATURE_TIA_OFF 0x06
#define OP_MODE_TEMPERATURE_TIA_ON  0x07

// ADS gain settings
#define ADS_GAIN_6_144V 0x0000
#define ADS_GAIN_4_096V 0x0200
#define ADS_GAIN_2_048V 0x0400
#define ADS_GAIN_1_024V 0x0600
#define ADS_GAIN_0_512V 0x0800
#define ADS_GAIN_0_256V 0x0A00

// Sensor configuration structure
struct sensorType
{
    double nanoAmperesPerPPM;
    double internalZeroCalibration;
    uint16_t adsGain;
    uint8_t TIA_GAIN_IN_KOHMS;
    uint8_t RLOAD;
    uint8_t REF_SOURCE;
    uint8_t INTERNAL_ZERO;
    uint8_t BIAS_SIGN;
    uint8_t BIAS;
    uint8_t FET_SHORT;
    uint8_t OP_MODE;
};

// Example sensor configurations
const sensorType SENSOR_CO = {
    70.0F,                    
    0.078,                    
    ADS_GAIN_4_096V,          
    TIA_GAIN_350_KOHM,        
    RLOAD_10_OHM,             
    REF_EXTERNAL,             
    INTERNAL_ZERO_20_PERCENT, 
    BIAS_SIGN_NEGATIVE,       
    BIAS_0_PERCENT,           
    FET_SHORT_DISABLED,       
    OP_MODE_3LEAD_AMP_CELL    
};

const sensorType SENSOR_NO2 = {
    -600.0F,                  
    -0.015,                   
    ADS_GAIN_2_048V,          
    TIA_GAIN_350_KOHM,        
    RLOAD_10_OHM,             
    REF_EXTERNAL,             
    INTERNAL_ZERO_67_PERCENT, 
    BIAS_SIGN_NEGATIVE,       
    BIAS_0_PERCENT,           
    FET_SHORT_DISABLED,       
    OP_MODE_3LEAD_AMP_CELL    
};

const sensorType SENSOR_SO2 = {
    400.0F,                   
    0.1,                    
    ADS_GAIN_2_048V,          
    TIA_GAIN_120_KOHM,        
    RLOAD_10_OHM,             
    REF_EXTERNAL,             
    INTERNAL_ZERO_20_PERCENT, 
    BIAS_SIGN_POSITIVE,       
    BIAS_0_PERCENT,           
    FET_SHORT_DISABLED,       
    OP_MODE_3LEAD_AMP_CELL    
};

#endif
