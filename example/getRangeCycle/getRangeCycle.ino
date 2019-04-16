/*!
   file getRangeCycle.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This sensor output the distance between sensor and obstacles
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-4-12
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
  /*The timing budget (TB) is the time required for the device to make one distance measurement*/
  /*TimingBudgetInMs = 15、20、33、50、100、200、500 ms*/
  sensor.setTimingBudgetInMs(20);
  /* The intermeasurement period  must be greater than or equal to the timing budget*/
  sensor.setInterMeasurementInMs(20);
  Serial.print("InterMeasurement:");
  Serial.println(sensor.getInterMeasurementInMs());
  Serial.print("TimingBudget:");
  Serial.println(sensor.getTimingBudgetInMs());
  
}

void loop(void)
{
  int distance
  distance = sensor.getDistance();
  Serial.print("Distance(mm): ");
  Serial.println(distance);
  
  Serial.println();
}