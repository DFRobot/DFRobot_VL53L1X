/*!
   file getDistance.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This demo can be used to calibrate the sensor(both of offset and cross talk)
   This demo output the distance between sensor and target
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2018-12-28
*/
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L1X.h"

DFRobot_VL53L1X sensor(&Wire);

void setup(void)
{
  Wire.begin();

  Serial.begin(9600);

  while (sensor.begin() != true){
    Serial.println("Sensor init failed!");
    delay(1000);
  }
  sensor.setOffset(30);             //This function apply the offset which found during calibration to the sensor
  //sensor.calibrateOffset(200);      //This function set a certain distance to finds the offset and applies the offset
  //sensor.setXTalk(30);              //This function apply the cross talk which found during calibration to the sensor
  //sensor.calibrateXTalk(400);       //This function set a certain distance to finds the cross talk and applies the cross talk
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