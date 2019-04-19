# VL53L1X

VL53L1X and VL53L0X are laser range sensors with three distance modes.<br>
VL53L1X's measurement range can reach up to 4m.<br>

## DFRobot_VL53L1X Library for RaspberryPi
---------------------------------------------------------
Provide a Raspberry Pi library for the VL53L1X modules.

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
This is a library for the RaspBerryPi, which can help RaspBerryPi to communicate with DFRobot_VL53L1X laser range sensor.<br>
The library makes it easy to configure the sensor via I2C and read range data from the sensor.<br>

## Feature
1. Serial input via I2C-bus
2. Max sampling rate given by I2C-bus speed
3. Operating voltage range from 2.6 to 3.5V

## Installation

This Sensor should work with VL53L1X on RaspberryPi.<br>
Run the program:
```
$> python VL53L1X.py

```

## Methods

```Python

'''
@brief Init The VL53L1X

@param smbus Bus = 1

'''
VL53L1X(1)

'''
@brief To judge which one is being used 

@return true if VL53L1X init succeed
@return false if VL53L1X init failed
'''
def begin(self)

'''
@brief enable range sensor
'''
def startRanging(self)

'''
@brief disable range sensor
'''
def stopRanging(self)

'''
@brief Set timing budget in ms(20,33,50,100,200,500)
'''
def setTimingBudgetInMs(self, timingBudget)

'''
@brief Get timing budget in ms

@return timing budget
'''
def getTimingBudgetInMs(self)

'''
@brief Set long distance mode
'''
def setDistanceModeLong(self)

'''
@brief Set short distance mode

@return The detailed distance
'''
def setDistanceModeShort(self)

'''
@brief Gets the distance mode

@return distance mode(2 for long or 1 for short)
'''
def getDistanceMode(self)

'''
@brief Set inter measurement in ms

@param interMeasurement must be greater than or equal to the timing budget
'''
def setInterMeasurementInMs(self, interMeasurement)

'''
@brief Get inter measurement in ms

@return inter measurement
'''
def getInterMeasurementInMs(self)

'''
@brief Gets the distansce

@return The detailed distance
'''
def getDistance(self) 

'''
@brief Set offset calibration

@param The detailed offset value(depends on sensor works)
'''
def setOffset(self, OffsetValue);

'''
@brief Set Xtalk calibration

@param The detailed Xtalk value(depends on sensor works)
'''
def setXTalk(self, XtalkValue);

'''
@brief Set distance threshold

@param ThreshLow(in mm) is the threshold under which the device raises an interrupt if window = 0
       ThreshHigh(in mm) is the threshold above which the device raises an interrupt if window = 1
       IntOnNoTarget is the window detection mode where 0 = below, 1 = above, 2 = out, and 3 = in
'''
def setDistanceThreshold(self, ThreshLow, ThreshHigh, Window)

'''
@brief Gets distance threshold window

@return The threshold window:0 = below, 1 = above, 2 = out, and 3 = in
'''
def getDistanceThresholdWindow(self);

'''
@brief Gets distance threshold low

@return The distance threshold low
'''
def getDistanceThresholdLow(self)

'''
@brief Gets distance threshold high

@return The distance threshold high
'''
def getDistanceThresholdHigh(self)

'''
@brief Sets calibrate offset

@param The target distance in mm
'''
def calibrateOffset(self, targetDistInMm)

'''
@brief Sets calibrate XTalk

@return The target distance in mm
'''
def calibrateXTalk(self, targetDistInMm)

'''
@brief 1D gesture
'''
def gesture(self)


```


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
