/*
* HR202_LIBRARY FOR ARDUINO
* LIBRARY VERSION: 1.0
* DEVELOPER: MATHEUS STEINMETZ (macusking)
* DATE FORMAT: MM/DD/YY
*BUILD DATE: 07/19/2023

* THIS IS AN OPEN-SOURCE PROJECT. FEEL FREE TO SHARE OR MODIFY AT YOUR WILL.
*/

#include "hr202_library.h"

HR202_SENSOR::HR202_SENSOR(long rs_value, int hum_pin, int tmp_pin, int ps_pin, int ps2_pin, int tmp_beta)
{
	resistor_value = rs_value;
	humidity_pin = hum_pin;
	thermistor_pin = tmp_pin;
	pulse_pin = ps_pin;
	pulse2_pin = ps2_pin;
	thermistor_beta = tmp_beta;
	last_reading_timer = 0;
	pinMode(pulse_pin, OUTPUT);
   	pinMode(pulse2_pin, OUTPUT);
	pinMode(thermistor_pin, INPUT);
	pinMode(humidity_pin, INPUT);
	first_reading = true;
}
		
float HR202_SENSOR::get_humidity()
{ 
	if(millis() - last_reading_timer > 5000 || first_reading) //AVOIDS YOU TO READ TOO FAST, WHICH IT'S NOT GOOD FOR THE SENSOR.
	{
		first_reading = false;
		
		//  POSITIVE POLARIZE THE SENSOR
		digitalWrite(pulse_pin, HIGH); 
		digitalWrite(pulse2_pin, LOW);

		resistance = analogRead(humidity_pin); // THIS WILL TAKE 109µs
		
		//  NEGATIVE POLARIZE THE SENSOR
		
		digitalWrite(pulse_pin, LOW); 
		digitalWrite(pulse2_pin, HIGH);

		delayMicroseconds(109); // ARTIFICIAL DELAY TO GIVE SIMETRIC 109µs AC 

		// NOW WE SHUT OFF THE MOISTURE SENSOR
		digitalWrite(pulse_pin, LOW); 
		digitalWrite(pulse2_pin, LOW);

		temperature = HR202_SENSOR::get_temperature(); // LET'S REQUEST A NEW TEMPERATURE READING

		resistance = (resistance * resistor_value) / (1024 - resistance); // LET'S CALCULATE THE RESISTANCE OF THE HR202 SENSOR.  

		//NOW LET'S CALCULATE THE ACTUAL RELATIVE HUMIDITY THROUGH REGRESSION EQUATIONS.
		if (temperature < 0)
		{
			humidity = 368 * pow(resistance, -0.158);
		}

		if (temperature >= 0 && temperature <5)
		{
			hum1 = 368 * pow(resistance, -0.158);
			hum2 = 383 * pow(resistance, -0.165);
			weight = 5 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 5 && temperature <10)
		{
			hum1 = 383 * pow(resistance, -0.165);
			hum2 = 388 * pow(resistance, -0.17);
			weight = 10 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 10 && temperature <15)
		{
			hum1 = 388 * pow(resistance, -0.17);
			hum2 = 421 * pow(resistance,-0.182);
			weight = 15 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 15 && temperature <20)
		{
			hum1 = 421 * pow(resistance,-0.182);
			hum2 = 426 * pow(resistance, -0.187);
			weight = 20 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 20 && temperature <25)
		{
			hum1 = 426 * pow(resistance, -0.187); 
			hum2 = 424 * pow(resistance, -0.19);
			weight = 25 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;

		}

		if(temperature >= 25 && temperature <30)
		{
			hum1 = 424 * pow(resistance, -0.19); 
			hum2 = 429 * pow(resistance, -0.195);
			weight = 30 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 30 && temperature <35)
		{
			hum1 = 429 * pow(resistance, -0.195); 
			hum2 = 429 * pow(resistance, -0.199);
			weight = 35 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 35 && temperature <40)
		{
			hum1 = 429 * pow(resistance, -0.199); 
			hum2 = 443 * pow(resistance, -0.205);
			weight = 40 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 40 && temperature <45)
		{
			hum1 = 443 * pow(resistance, -0.205); 
			hum2 =  453 * pow(resistance, -0.211);
			weight = 45 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 45 && temperature <50)
		{
			hum1 =  453 * pow(resistance, -0.211); 
			hum2 = 449 * pow(resistance, -0.214);
			weight = 50 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 50 && temperature <55)
		{
			hum1 = 449 * pow(resistance, -0.214); 
			hum2 =  459 * pow(resistance, -0.22);
			weight = 55 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 55 && temperature <60)
		{
			hum1 = 459 * pow(resistance, -0.22); 
			hum2 =  458 * pow(resistance, -0.223);
			weight = 60 - temperature;
			humidity = (hum1 * weight) + (hum2 * (5 - weight));
			humidity /= 5.00;
		}

		if(temperature >= 60)
		{
			humidity =  458 * pow(resistance, -0.223);
		}
			
		last_reading_timer = millis();

		return humidity; //WINNER WIINER, CHICKEN DINNER!
	}
	
	else // IN CASE YOU'RE READING TOO FAST, LET'S RETURN THE LAST READING VALUE
	{
		return humidity;
	} 
}

float HR202_SENSOR::get_temperature() // FOR  TEMPERATURE, LET'S USE STEINHART'S EQUATION APPROACH.
{
	adc_temp = analogRead(thermistor_pin);
	adc_temp = map(adc_temp, 0, 1023, 1023, 0); 
	adc_temp = 1024 / adc_temp - 1;
	adc_temp = 10000 * adc_temp;
	steinhart = adc_temp / 10000; 
	steinhart = logf(steinhart);                 
	steinhart /= thermistor_beta;                  
	steinhart += 1.0 / (25 + 273.15); 
	steinhart = 1.0 / steinhart;                 
	steinhart -= 273.15; 
	return (steinhart);
}
