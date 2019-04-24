/*!
   file getDistance.ino
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
uint16_t actDistance;

void setup(void)
{
  Wire.begin();

  Serial.begin(9600);

  while (sensor.begin() != true){
    Serial.println("Sensor init failed!");
    delay(1000);
  }
  
  actDistance = 208;
  Serial.print("ActDistance(mm): ");
  Serial.println(actDistance);
  
  //sensor.setOffset(20);             //This function apply the offset which found during calibration to the sensor
  sensor.calibrateOffset(actDistance); //This function set a certain distance to finds the offset and applies the offset
  Serial.print("Offset(mm): ");
  Serial.println(sensor.getOffset());
  
  //sensor.setXTalk(0);              //This function apply the cross talk which found during calibration to the sensor
  sensor.calibrateXTalk(actDistance);       //This function set a certain distance to finds the cross talk and applies the cross talk
  Serial.print("XTalk(cps): ");
  Serial.println(sensor.getXTalk());
  Serial.println();
}

void loop(void)
{
  sensor.startRanging();
  int distance = sensor.getDistance();
  sensor.stopRanging();

  Serial.print("Distance(mm): ");
  Serial.println(distance);

  Serial.println();
  delay(1000);
}