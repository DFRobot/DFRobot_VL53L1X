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
import threading
from gpio import GPIO
sys.path.append('../')
from DFRobot_VL53L1X import VL53L1X



sensor = VL53L1X(1) #VL53L1X begin
#sensor.setInterruptPolarityHigh()
sensor.setDistanceThreshold(200, 400, 0)#ThreshLow, ThreshHigh, Window(0 = below, 1 = above, 2 = out and 3 = in)
print(sensor.getDistanceThresholdWindow())
print(sensor.getDistanceThresholdLow())
print(sensor.getDistanceThresholdHigh())
#sensor.checkForDataReady()
sensor.setDistanceModeShort()
#sensor.setDistanceModeLong()
sensor.startRanging()
time.sleep(0.1)
'''
while True:
    GPIO_OUT_PIN = 21
    pinOut = GPIO(GPIO_OUT_PIN, GPIO.OUT)
    pinOut.setOut(GPIO.LOW)
    time.sleep(1)
    pinOut.setOut(GPIO.HIGH)
    time.sleep(1)
'''
IO1 = 21
IO1Lock = threading.Lock()
IO1Flag = False

def IO1CallBack():
  global IO1Lock, IO1Flag
  IO1Lock.acquire() # wait key A lock release
  IO1Flag = True
  IO1Lock.release()
 
io1 = GPIO(IO1, GPIO.IN)
io1.setInterrupt(GPIO.RISING, IO1CallBack)


def main():
    global IO1Lock, IO1Flag
    while True:
        #print(sensor.checkForDataReady())
        print ("Distance   : %.2f " % sensor.getDistance())
        print (" ")
        if IO1Flag:
            IO1Lock.acquire() # wait io1 release
            IO1Flag = False
            IO1Lock.release()
            print("distance is below 200mm")
            print()
            time.sleep(0.1)
        time.sleep(1)

if __name__ == "__main__":
    main()
