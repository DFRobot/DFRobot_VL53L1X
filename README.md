# VL53L1X


VL53L1X is laser range sensors with three distance modes.<br>
VL53L1X's measurement range can reach up to 4m.<br>

## DFRobot_VL53L1X Library for Arduino
---------------------------------------------------------
Provide an Arduino library for the VL53L1X modules.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary
This is a library for the Arduino IDE, which can help Arduino to communicate with DFRobot_VL53L1X laser range sensor.<br>
The library makes it easy to configure the sensor via I2C and read range data from the sensor.<br>
This library is compatible with DFRobot_VL53L0X.<br>

## Feature
1. Low standby current
2. Serial input via I2C-bus
3. Max sampling rate given by I2C-bus speed
4. I2C address can be modified by modifying the macro definition
5. Operating voltage range from 2.6 to 3.5V

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_VL53L1X.h"

/* 
 * @brief To judge which one is being used 
 *
 * @return true if VL53L1X init succeed
 * @return false if VL53L1X init failed
 */
bool DFRobot_VL53L1X::begin();

/*
 * @brief Set the I2C address
 *
 */
void setI2CAddress(uint8_t addr);

/*
 * @brief Gets the current I2C address
 *
 * @return The I2C address
 */
int getI2CAddress();

/*
 * @brief Sets interrupt polarity high
 *
 */
void setInterruptPolarityHigh();

/*
 * @brief Sets interrupt polarity low
 *
 */
void setInterruptPolarityLow();

/*
 * @brief Sets interrupt polarity(1 is high,0 is low)
 *
 */
void setInterruptPolarity(uint8_t NewPolarity);

/*
 * @brief Gets the interrupt polarity
 *
 * @return The interrupt polarity(1 is high,0 is low)
 */
uint8_t getInterruptPolarity();

/*
 * @brief enable range sensor
 *
 */
void startRanging();

/*
 * @brief disable range sensor
 *
 */
void stopRanging();

/*
 * @brief Set timing budget in ms(20、33、50、100、200、500)
 *
 */
void setTimingBudgetInMs(uint16_t timingBudget);

/*
 * @brief Get timing budget in ms
 *
 * @return timing budget
 */
uint16_t getTimingBudgetInMs();

/*
 * @brief Set long distance mode
 *
 */
void setDistanceModeLong();

/*
 * @brief Set short distance mode
 *
 * @return The detailed distance
 */
void setDistanceModeShort();

/*
 * @brief Set distance mode
 *
 * @param distance mode(long or short)
 */
void setDistanceMode(uint16_t DM);

/*
 * @brief Gets the distance mode
 *
 * @return distance mode(long or short)
 */
uint8_t getDistanceMode();

/*
 * @brief Set inter measurement in ms
 *
 * @param interMeasurement must be greater than or equal to the timing budget
 */
void setInterMeasurementInMs(uint16_t interMeasurement);

/*
 * @brief Get inter measurement in ms
 *
 * @return inter measurement
 */
uint16_t getInterMeasurementInMs();

/*
 * @brief Gets the distansce
 *
 * @return The detailed distance
 */
uint16_t getDistance(); 


/*
 * @brief Set offset calibration
 *
 * @param The detailed offset value(depends on sensor works)
 */
void setOffset(int16_t OffsetValue);

/*
 * @brief Get offset calibration
 *
 * @return The detailed offset value
 */
int16_t getOffset();

/*
 * @brief Set Xtalk calibration
 *
 * @param The detailed Xtalk value(depends on sensor works)
 */
void setXTalk(uint16_t XtalkValue);

/*
 * @brief Get Xtalk calibration
 *
 * @return The detailed Xtalk value
 */
uint16_t getXTalk(); 

/*
 * @brief Set distance threshold
 *
 * @param ThreshLow(in mm) is the threshold under which the device raises an interrupt if window = 0
 *        ThreshHigh(in mm) is the threshold above which the device raises an interrupt if window = 1
 *        IntOnNoTarget is the window detection mode where 0 = below, 1 = above, 2 = out, and 3 = in
 */
void setDistanceThreshold(uint16_t ThreshLow, uint16_t ThreshHigh, uint8_t Window);

/*
 * @brief Gets distance threshold window
 *
 * @return The threshold window:0 = below, 1 = above, 2 = out, and 3 = in
 */
uint16_t getDistanceThresholdWindow();

/*
 * @brief Gets distance threshold low
 *
 * @return The distance threshold low
 */
uint16_t getDistanceThresholdLow();

/*
 * @brief Gets distance threshold high
 *
 * @return The distance threshold high
 */
uint16_t getDistanceThresholdHigh(); 

/*
 * @brief Set programs the ROI
 *
 * @param X is the ROI width and Y is the ROI height
 */
void setROI(uint16_t X, uint16_t Y);

/*
 * @brief This function programs a new signal threshold in kcps where the default is 1024 kcps
 *
 * @param Default is 1024 kcps
 */
void setSignalThreshold(uint16_t Signal);

/*
 * @brief Gets current signal threshold
 *
 * @return The  current signal threshold in kcps
 */
uint16_t getSignalThreshold(); 

/*
 * @brief Sets calibrate offset
 *
 * @param The target distance in mm
 */
void calibrateOffset(uint16_t targetDistInMm);

/*
 * @brief Sets calibrate XTalk
 *
 * @return The target distance in mm
 */
void calibrateXTalk(uint16_t targetDistInMm);

/*
 * @brief 1D gesture
 */
uint8_t gesture();

eVL53L1X_Status lastOperateStatus;
```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
RaspberryPi |       √      |             |            | 


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
