'''
file getDistance.py
SEN0302 and SEN0245 Distance Ranging Sensor
The module is connected with RaspberryPi to read the distance
This sensor output the distance between sensor and obstacles
Copyright    [DFRobot](http://www.dfrobot.com), 2018
Copyright    GNU Lesser General Public License
version  V1.0
date  2018-12-11
'''

import time
import sys
sys.path.append('../')
from DFRobot_VL53L1X import VL53L1X

vl53l1x = VL53L1X(1) #VL53L1X begin
sensor.setDistanceThreshold(200, 300, 0);#ThreshLow, ThreshHigh, Window(0 = below, 1 = above, 2 = out and 3 = in)
print(sensor.getDistanceThresholdWindow())
print(sensor.getDistanceThresholdLow())
print(sensor.getDistanceThresholdHigh())
sensor.setDistanceModeShort()
#sensor.setDistanceModeLong()
sensor.startRanging()

def main():
    while True:
        time.sleep(1)
        print ("Distance   : %.2f " % vl53l1x.getDistance())
        print (" ")

if __name__ == "__main__":
    main()