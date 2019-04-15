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

sensor = VL53L1X(1) #VL53L1X begin

def main():
    while True:
        sensor.startRanging()
        gesStatus = 0
        for i in range(0,1000):
            gesStatus = sensor.gesture()
            if(gesStatus == 1):
                print("Current Gesture: DOWN")
            elif(gesStatus == 2):
                print("Current Gesture: UP")
            else:
                time.sleep(0.1)
            time.sleep(0.2)
        sensor.stopRanging()
    
        print()

if __name__ == "__main__":
    main()