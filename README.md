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

## Feature
1. Serial input via I2C-bus
2. Max sampling rate given by I2C-bus speed
3. Operating voltage range from 2.6 to 3.5V

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>

## Methods

```C++

#include "DFRobot_VL53L1X.h"

/*
 * @brief init Wire
 */
DFRobot_VL53L1X(TwoWire *pWire);

/* 
 * @brief To judge which one is being used 
 *
 * @return true if VL53L1X init succeed
 * @return false if VL53L1X init failed
 */
bool DFRobot_VL53L1X::begin();

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
 * @param eTimingBudget eBudget1 = 20
                        eBudget2 = 33
                        eBudget3 = 50
                        eBudget4 = 100
                        eBudget5 = 200
                        eBudget6 = 500
 */
void setTimingBudgetInMs(uint16_t timingBudget);
s
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
 *        IntOnNoTarget is the window detection mode where 0 = eBelow, 1 = eAbove, 2 = eOut, and 3 = eIn
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

/*
 * @brief 1D eVL53L1X_ok            for ok 
 *           eVL53L1X_InitError     for init error
 *           eVL53L1X_WriteRegError for I2C write error
 *           eVL53L1X_ReadRegError  for I2C read error
 */
eVL53L1X_Status lastOperateStatus;
```



## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
RaspberryPi |       √      |             |            | 


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
