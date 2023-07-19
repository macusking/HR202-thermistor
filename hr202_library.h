/*
* HR202_LIBRARY FOR ARDUINO
* LIBRARY VERSION: 1.0
* DEVELOPER: MATHEUS STEINMETZ (macusking)
* DATE FORMAT: MM/DD/YY
*BUILD DATE: 07/19/2023

* THIS IS AN OPEN-SOURCE PROJECT. FEEL FREE TO SHARE OR MODIFY AT YOUR WILL.
*/

#ifndef _HR202_
#define _HR202_

#include "Arduino.h"

class HR202_SENSOR
{
	public:
	bool first_reading;
    long resistor_value;
    int thermistor_beta;
    int weight;
    int humidity_pin;
    int thermistor_pin;
    int pulse_pin;
    int pulse2_pin;
    unsigned long resistance;
	unsigned long last_reading_timer;
    float hum1;
    float hum2;
    float adc_temp;
    float temperature;
    float humidity;
    float steinhart;
	float get_humidity();
	float get_temperature();
    HR202_SENSOR(long rs_value, int hum_pin, int tmp_pin, int ps_pin, int ps2_pin, int tmp_beta);
};		
#endif