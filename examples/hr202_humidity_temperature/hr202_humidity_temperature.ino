/*
* HR202_LIBRARY FOR ARDUINO DEMO
* LIBRARY VERSION: 1.0
* DEVELOPER: MATHEUS STEINMETZ (macusking)
* DATE FORMAT: MM/DD/YY
* BUILD DATE: 07/19/2023

* THIS IS AN OPEN-SOURCE PROJECT. FEEL FREE TO SHARE OR MODIFY AT YOUR WILL.

WIRING DIAGRAM:

Thermistor:

[+5V]----------[10k resistor]-----(analog temp_pin)------[10k NTC]------------ [GROUND]

HR202 sensor:

[pulse_pin] -------- [10k resistor]-------(analog humidity_pin)----------[HR202]--------[pulse2_pin]

*/

#include "hr202_library.h"
#include <Wire.h>

HR202_SENSOR SENSOR1(10000, A0 , A1, 5, 6, 3950); // HR202 SERIES RESISTOR, HUMIDITY PIN, TEMPERATURE PIN, PULSE PIN, PULSE 2 PIN, Thermistor BETA

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  float temperature = SENSOR1.get_temperature();
  float humidity = SENSOR1.get_humidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(10000);
}
