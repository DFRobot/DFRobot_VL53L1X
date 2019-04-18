/*!
   file getRangeCycle.ino
   SEN0302 Distance Ranging Sensor
   The module is connected with Arduino Uno to read the distance
   This demo can set timing budget and inter measurement
   This demo output the distance between sensor and obstacles at the inter measurement that you set
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-4-18
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
  sensor.setDistanceModeShort();
  /*The timing budget (TB) is the time the sensor needed to complete one distance measurement*/
  /*TimingBudgetInMs = eBudget1 = 20ms
                       eBudget2 = 33ms
                       eBudget3 = 50ms
                       eBudget4 = 100ms
                       eBudget5 = 200ms
                       eBudget6 = 500ms
   */
  sensor.setTimingBudgetInMs(eBudget1);
  /* The intermeasurement period  must be greater than or equal to the timing budget*/
  sensor.setInterMeasurementInMs(20);
  Serial.print("InterMeasurement:");
  Serial.println(sensor.getInterMeasurementInMs());
  Serial.print("TimingBudget:");
  Serial.println(sensor.getTimingBudgetInMs());
  sensor.startRanging();
}

void loop(void)
{
  while (sensor.checkForDataReady() == true){
    int distance;
    distance = sensor.getDistance();
    Serial.print("Distance(mm): ");
    Serial.println(distance);
    Serial.println();
  }
}