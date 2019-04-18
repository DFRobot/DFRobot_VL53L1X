'''
file get_distance.py
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
        sensor.start_ranging()
        gesStatus = 0
        distance = sensor.get_distance()
        while distance < 400:
            gesStatus = sensor.gesture()
            if(gesStatus == 1):
                print("Current Gesture: DOWN")
                time.sleep(0.1)
            elif(gesStatus == 2):
                print("Current Gesture: UP")
                time.sleep(0.1)
            else:
                time.sleep(0.1)
            time.sleep(0.1)
        sensor.stop_ranging()

if __name__ == "__main__":
    main()