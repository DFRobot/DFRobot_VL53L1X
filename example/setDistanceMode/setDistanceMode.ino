/*!
   file getDistance.ino
   SEN0302 SEN0245 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This sensor output the distance between sensor and obstacles
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-4-8
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
  attachInterrupt(0, interrupt, RISING);
  sensor.setDistanceThreshold(200, 300, 0);//ThreshLow, ThreshHigh, Window(0 = below, 1 = above, 2 = out and 3 = in)
  Serial.println(sensor.getDistanceThresholdWindow());
  Serial.println(sensor.getDistanceThresholdLow());
  Serial.println(sensor.getDistanceThresholdHigh());
  sensor.setDistanceModeShort();
  sensor.startRanging();
  //sensor.checkForDataReady();
  delay(100);
}

void loop() 
{
  int distance
  distance = sensor.getDistance();
  //Serial.print("Distance(mm): ");
  //Serial.println(distance);
  
  Serial.println();
  delay(1000);
}

void interrupt(){
  Serial.println("distance is below 200mm");
  Serial.println();
  delay(1000);
}