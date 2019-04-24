/*!
   file velocity.ino
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

float dis1 = 0;
float dis2;
uint16_t time;
float speed;
int i = 0;

void setup(void)
{
    Wire.begin();

    Serial.begin(9600);

    while (sensor.begin() != true){
        Serial.println("Sensor init failed!");
        delay(1000);
    }
    sensor.setDistanceModeShort();
    sensor.setTimingBudgetInMs(eBudget_500ms);
    sensor.setInterMeasurementInMs(500);
    Serial.print("InterMeasurement:");
    Serial.println(sensor.getInterMeasurementInMs());
    Serial.print("TimingBudget:");
    Serial.println(sensor.getTimingBudgetInMs());
    time = sensor.getInterMeasurementInMs();
    sensor.startRanging();
    delay(100);
}

void loop(void)
{
    while (sensor.checkForDataReady() == true){
        dis2 = dis1;
        dis1 = sensor.getDistance();
        speed = (dis1/time) - (dis2/time);
        if(abs(speed) < 2){
            if(speed > 0){
                Serial.print("Target is go away ,   speed is ");
                Serial.print(speed);
                Serial.println(" m/s");
            }else{
                Serial.print("Target is get closed ,speed is ");
                Serial.print(speed);
                Serial.println(" m/s");
            }
        }else
            Serial.println("No target");
    }
}
