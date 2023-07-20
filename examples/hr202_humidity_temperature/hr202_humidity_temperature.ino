/*
* HR202_LIBRARY FOR ARDUINO DEMO
* LIBRARY VERSION: 1.0
* DEVELOPER: MATHEUS STEINMETZ (macusking)
* DATE FORMAT: MM/DD/YY
* BUILD DATE: 07/20/2023 

 WIRING:
     THERMISTOR:
            5V ---- 10K ---- (TEMPERATURE_PIN) ---- NTC THERMISTOR ---- GROUND
      HR202:
            PULSE1_PIN ---- 10K ---- (HUMIDITY_PIN) ---- HR202 ---- PULSE2_PIN

* THIS IS AN OPEN-SOURCE PROJECT. FEEL FREE TO SHARE OR MODIFY AT YOUR WILL.
*/

#include <hr202_library.h>
#include <Wire.h>

#define SERIES_RESISTOR 10000 //  HR202 SERIES RESISTOR. RECOMMENDED VALUE IS 10k
#define HUMIDITY_PIN A0   //  HR202 HUMIDITY READING PIN (ANALOG PIN)
#define TEMPERATURE_PIN A1  // THERMISTOR READING PIN (ANALOG PIN)
#define PULSE1_PIN 5  // PULSE PIN FOR HR202 (DIGITAL PIN)
#define PULSE2_PIN 6  //  PULSE2 PIN FOR HR202 (DIGITAL PIN)
#define THERMISTOR_BETA 3950  //  THERMISTOR BETA VALUE (TYPICAL VALUE IS AROUND 3000 ~ 4000. READ THERMISTOR'S DATASHEET)


HR202_SENSOR SENSOR1(SERIES_RESISTOR, HUMIDITY_PIN , TEMPERATURE_PIN, PULSE1_PIN, PULSE2_PIN, THERMISTOR_BETA);

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

  delay(5000);
}
