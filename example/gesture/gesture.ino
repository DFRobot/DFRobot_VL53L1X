/*!
   file gesture.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This demo can get the 1D gesture(up and down)
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2018-4-12
*/
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L1X.h"

// volatile  int8_t GPIO1TRIG = 0;

DFRobot_VL53L1X sensor(&Wire);

void setup(void)
{
    Wire.begin();

    Serial.begin(9600);

    while (sensor.begin() != true){
        Serial.println("Sensor init failed!");
        delay(1000);
    }
}

void loop(void)
{
    sensor.startRanging();
    uint8_t gesStatus;
    int i;
    while(i < 1000 && sensor.getDistance() < 400){
        gesStatus = sensor.gesture();
        if(gesStatus == 1){
            Serial.println("Current Gesture: DOWN");
            delay(200);
        } else if(gesStatus == 2){
            Serial.println("Current Gesture: UP");
            delay(200);
        }else
            delay(200);
        i++;
        delay(200);
    }
    sensor.stopRanging();
    delay(200);
}
