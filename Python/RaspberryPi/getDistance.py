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
while not sensor.begin():
    time.sleep(2)
sensor.setOffset(30)
#sensor.calibrateOffset(200)
#sensor.setXTalk(400)
#sensor.calibrateXTalk(400)
#sensor.reset()

def main():
    while True:
        sensor.startRanging()
        time.sleep(1)
        print ("Distance   : %.2f " % sensor.getDistance())
        print (" ")
        sensor.stopRanging()

if __name__ == "__main__":
    main()