/*!
   file getDistance.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This sensor output the distance between sensor and obstacles
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
  sensor.setOffset(30);
  //sensor.calibrateOffset(200);
  // sensor.setXTalk(400);
  // sensor.calibrateXTalk(400);
  
  Serial.println(sensor.getI2CAddress());
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