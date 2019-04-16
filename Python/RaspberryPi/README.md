# VL53L1X

VL53L1X and VL53L0X are laser range sensors with three distance modes.<br>
VL53L0X's measurement range can reach up to 2m.<br>
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
This is a library for the Arduino IDE, which can help Arduino to communicate with DFRobot_VL53L1X laser range sensor.<br>
The library makes it easy to configure the sensor via I2C and read range data from the sensor.<br>
The library is compatible with DFRobot_VL53L0X.<br>

## Feature
1. Low standby current
2. Serial input via I2C-bus
3. Max sampling rate given by I2C-bus speed
4. I2C address can be modified by modifying the macro definition
5. Operating voltage range from 2.6 to 3.5V

## Installation

This Sensor should work with VL53L1X on RaspberryPi.<br>
Run the program:
```
$> python VL53L1X.py

```

## Methods

```Python


'''
@brief To judge which one is being used 

@return true if VL53L1X init succeed
@return false if VL53L1X init failed
'''
def begin(self)
 
'''
@brief Set the I2C address
'''
def (self, addr)

'''
@brief Gets the current I2C address

@return The I2C address
'''
def getI2CAddress(self)

'''
@brief Sets interrupt polarity high
'''
def setInterruptPolarityHigh(self)

'''
@brief Sets interrupt polarity low
'''

def setInterruptPolarityLow(self)

'''
@brief Sets interrupt polarity(1 is high,0 is low)
'''
def setInterruptPolarity(self, NewPolarity)

'''
@brief Gets the interrupt polarity

@return The interrupt polarity(1 is high,0 is low)
'''
def getInterruptPolarity(self)

'''
@brief enable range sensor
'''
def startRanging(self)

'''
@brief disable range sensor
'''
def stopRanging(self)

'''
@brief Set timing budget in ms(15?20?33?50?100?200?500)
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
@brief Set distance mode

@param distance mode(long or short)
'''
def setDistanceMode(self, DM);

'''
@brief Gets the distance mode

@return distance mode(long or short)
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
@brief Get offset calibration

@return The detailed offset value
'''
def getOffset(self)

'''
@brief Set Xtalk calibration

@param The detailed Xtalk value(depends on sensor works)
'''
def setXTalk(self, XtalkValue);

'''
@brief Get Xtalk calibration

@return The detailed Xtalk value
'''
def getXTalk(self);

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
@brief Set programs the ROI

@param X is the ROI width and Y is the ROI height
'''
def setROI(self, X, Y)

'''
@brief This function programs a new signal threshold in kcps where the default is 1024 kcps

@param Default is 1024 kcps
'''
def setSignalThreshold(self, Signal);

'''
@brief Gets current signal threshold

@return The  current signal threshold in kcps
'''
def getSignalThreshold(self)

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
