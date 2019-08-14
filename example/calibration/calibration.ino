/*!
   file calibration.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This demo can be used to calibrate the sensor(both of offset and cross talk)
   This demo output the distance between sensor and target
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-4-22
*/
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L1X.h" 

DFRobot_VL53L1X sensor(&Wire);
uint16_t actDistance = 100; //actual distace 100mm
int16_t offset = 0;

void setup(void)
{
  Wire.begin();
  Serial.begin(9600);
  while (sensor.begin() != true){
    Serial.println("Sensor init failed!");
    delay(1000);
  }
  Serial.print("ActDistance(mm): ");
  Serial.println(actDistance);
  
  //sensor.setOffset(offset);                 //This function apply the offset which found during calibration to the sensor
  offset = sensor.getOffset();
  Serial.print("Offset(mm): ");
  Serial.println(offset);
  Serial.println("offset = actDistance - Distance");// offset = targetDistance - sensorDistance
  Serial.println();
}

void loop(void)
{
  sensor.startRanging();
  uint16_t distance = sensor.getDistance();
  sensor.stopRanging();
  offset = actDistance - distance;

  Serial.print("Distance(mm): ");
  Serial.println(distance);
  Serial.print("offset(mm): ");
  Serial.println(offset);

  Serial.println();
  delay(1000);
}