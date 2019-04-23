'''
file gesture.py
SEN0302 and SEN0245 Distance Ranging Sensor
The module is connected with RaspberryPi to read the distance
This demo can get the 1D gesture(up and down)
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
    time.sleep(1)

dis1 = 0

def main():
    while True:
        while sensor.check_for_data_ready() == True:
            dis2 = dis1;
            dis1 = sensor.get_distance()
            speed = (dis1/time) - (dis2/time)
            if(abs(speed) < 2):
                if speed > 0:
                    print("Target is go away ,   speed is %.f" % speed " m/s")
                else:
                    print("Target is get closed ,speed is %.f" % speed " m/s")
                
            else:
                print("No target")
    

if __name__ == "__main__":
    main()