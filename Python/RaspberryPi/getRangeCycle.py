'''
file getRangeCycle.py
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

sensor = VL53L1X(1) #VL53L1X begin
sensor.setDistanceModeLong()
'''
The timing budget (TB) is the time required for the device to make one distance measurement
TimingBudgetInMs = 20,33,50,100,200,500 ms
'''
sensor.setTimingBudgetInMs(15)
'''
The intermeasurement period  must be greater than or equal to the timing budget
'''
sensor.setInterMeasurementInMs(50)
print("InterMeasurement  : %.1f " % sensor.getInterMeasurementInMs())
print("TimingBudget      : %.1f " % sensor.getTimingBudgetInMs())

def main():
    while True:
        time.sleep(1)

if __name__ == "__main__":
    main()