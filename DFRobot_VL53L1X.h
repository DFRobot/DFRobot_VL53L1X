#include "Wire.h"
#include "Arduino.h"

#define VL53L1X_IMPLEMENTATION_VER_MAJOR       1
#define VL53L1X_IMPLEMENTATION_VER_MINOR       0
#define VL53L1X_IMPLEMENTATION_VER_SUB         1
#define VL53L1X_IMPLEMENTATION_VER_REVISION  0000

#define SOFT_RESET                                            0x0000
#define VL53L1_I2C_SLAVE__DEVICE_ADDRESS                      0x0001
#define VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND          0x0008
#define ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS        0x0016
#define ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS    0x0018
#define ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS    0x001A
#define ALGO__PART_TO_PART_RANGE_OFFSET_MM                    0x001E
#define MM_CONFIG__INNER_OFFSET_MM                            0x0020
#define MM_CONFIG__OUTER_OFFSET_MM                            0x0022
#define GPIO_HV_MUX__CTRL                                     0x0030
#define GPIO__TIO_HV_STATUS                                   0x0031
#define SYSTEM__INTERRUPT_CONFIG_GPIO                         0x0046
#define PHASECAL_CONFIG__TIMEOUT_MACROP                       0x004B
#define RANGE_CONFIG__TIMEOUT_MACROP_A_HI                     0x005E
#define RANGE_CONFIG__VCSEL_PERIOD_A                          0x0060
#define RANGE_CONFIG__VCSEL_PERIOD_B                          0x0063
#define RANGE_CONFIG__TIMEOUT_MACROP_B_HI                     0x0061
#define RANGE_CONFIG__TIMEOUT_MACROP_B_LO                     0x0062
#define RANGE_CONFIG__SIGMA_THRESH                            0x0064
#define RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS           0x0066
#define RANGE_CONFIG__VALID_PHASE_HIGH                        0x0069
#define VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD                0x006C
#define SYSTEM__THRESH_HIGH                                   0x0072
#define SYSTEM__THRESH_LOW                                    0x0074
#define SD_CONFIG__WOI_SD0                                    0x0078
#define SD_CONFIG__INITIAL_PHASE_SD0                          0x007A
#define ROI_CONFIG__USER_ROI_CENTRE_SPAD                      0x007F
#define ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE         0x0080
#define SYSTEM__SEQUENCE_CONFIG                               0x0081
#define VL53L1_SYSTEM__GROUPED_PARAMETER_HOLD                 0x0082
#define SYSTEM__INTERRUPT_CLEAR                               0x0086
#define SYSTEM__MODE_START                                    0x0087
#define VL53L1_RESULT__RANGE_STATUS                           0x0089
#define VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0         0x008C
#define RESULT__AMBIENT_COUNT_RATE_MCPS_SD                    0x0090
#define VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0                  0x0096
#define VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0     0x0098
#define VL53L1_RESULT__OSC_CALIBRATE_VAL                      0x00DE
#define VL53L1_FIRMWARE__SYSTEM_STATUS                        0x00E5
#define VL53L1_IDENTIFICATION__MODEL_ID                       0x010F
#define VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD               0x013E


#define VL53L1X_DEFAULT_DEVICE_ADDRESS                        0x52

#define ALGO__PART_TO_PART_RANGE_OFFSET_MM    0x001E
#define MM_CONFIG__INNER_OFFSET_MM            0x0020
#define MM_CONFIG__OUTER_OFFSET_MM             0x0022

enum eVL53L1X_Status{
    eVL53L1X_ok,
    eVL53L1X_InitError,
    eVL53L1X_WriteRegError,
    eVL53L1X_ReadRegError,
};

class DFRobot_VL53L1X
{
    public:
        DFRobot_VL53L1X(TwoWire *pWire){_pWire = pWire;};
        bool begin();
        //VL53L1X_Version_t getSoftwareVersion();
        void setI2CAddress(uint8_t addr);
        int getI2CAddress();
        void setInterruptPolarityHigh();
        void setInterruptPolarityLow();
        void setInterruptPolarity(uint8_t NewPolarity);
        uint8_t getInterruptPolarity();
        void startRanging();
        void stopRanging();
        void setTimingBudgetInMs(uint16_t timingBudget);
        uint16_t getTimingBudgetInMs();
        bool checkForDataReady();
        void setDistanceModeLong();
        void setDistanceModeShort();
        void setDistanceMode(uint16_t DM);
        uint8_t getDistanceMode();
        void setInterMeasurementInMs(uint16_t interMeasurement);
        uint16_t getInterMeasurementInMs();
        uint16_t getDistance(); 
        uint8_t getRangeStatus(); 
        //uint16_t checkInterrupt();
        void setOffset(int16_t OffsetValue);
        int16_t getOffset();
        void setXTalk(uint16_t XtalkValue);
        uint16_t getXTalk(); 
        void setDistanceThreshold(uint16_t ThreshLow, uint16_t ThreshHigh, uint8_t Window);
        uint16_t getDistanceThresholdWindow();
        uint16_t getDistanceThresholdLow();
        uint16_t getDistanceThresholdHigh(); 
        void setROI(uint16_t X, uint16_t Y);
        void setSignalThreshold(uint16_t Signal);
        uint16_t getSignalThreshold(); 
        void calibrateOffset(uint16_t targetDistInMm);
        void calibrateXTalk(uint16_t targetDistInMm);
        uint8_t gesture();
        eVL53L1X_Status lastOperateStatus;
    private:
        TwoWire *_pWire;
        void sensorOn();
        void sensorOff();
        
        uint16_t getSignalPerSpad();
        uint16_t getAmbientPerSpad();
        uint16_t getSignalRate(); 
        uint16_t getSpadNb();
        uint16_t getAmbientRate(); 
        uint16_t getROIX(); 
        uint16_t getROIY(); 
        void setSigmaThreshold(uint16_t Sigma);
        uint16_t getSigmaThreshold(); 
        void startTemperatureUpdate();
        void clearInterrupt();
        void writeByteData(uint16_t index, uint8_t data);
        void writeWordData(uint16_t index, uint16_t data);
        void writeWordData32(uint16_t index, uint32_t data);
        void readByteData(uint16_t index, uint8_t *data);
        void readWordData(uint16_t index, uint16_t *data);
        void readWordData32(uint16_t index, uint32_t *data);
        void updateByte(uint16_t index, uint8_t AndData, uint8_t OrData);
        void writeMulti(uint16_t index, uint8_t *pdata, uint32_t count);
        void readMulti(uint16_t index, uint8_t *pdata, uint32_t count);
        void i2CWrite(uint16_t reg, uint8_t *pBuf, uint16_t len);
        void i2CRead(uint16_t reg, uint8_t *pBuf, uint16_t len);
    
        uint8_t   addr = 0x29;
        uint8_t   _addr;
        int16_t   dis1;
        int16_t   dis2 = 0;
};