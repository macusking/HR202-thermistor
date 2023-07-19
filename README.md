# HR202-thermistor
A simple temperature + humidity library for Arduino using HR202 humidity sensor and a NTC thermistor.

This library will generate the proper AC current over the HR202, in a 109µs pulse, avoiding polarization and maintaining the sensor in proper working conditions for years to come! The HR202 sensor cannot be used in a DC voltage divider configuration, otherwise it will have a short lifespan! Temperature data is required in order to convert HR202 readings into relative humidity, therefore, we included the NTC thermistor while developing this library.

For using this library, you'll need the following components:
1) 2 x 10k resistors
2) 1 x 10k @ 25°c thermistor
3) 1 x HR202 humidity sensor

It's worth mentioning that this library will make use of 4 Arduino pins (2 x digitals + 2 x analogs). These two digital pins are used for generating the AC pulse across the HR202 sensor. The 2 analogs pins are for reading the temperature and humidity sensors.

KEYS BENEFITS OF USING THE HR202 SENSOR:
1) It's damn cheap! You can buy for cents each.
2) It's pretty stable over time. Drifts due to contamination are very low.
3) it can provide accurate readings for most applications.
4) Thermistors are also pretty cheap. You can have a fully functional thermo-hygrometer for less than $1.

LIMITATIONS:
1) This isn't a super-high accuracy sensor. It has an accuracy of +- 5%, which is good for most applications.
2) This sensor is rated for 20 - 90% RH. The library will delivery output values below 20% and above 90%, however these values are interpolation data. It's only +-5% accurate between 20-90% RH zone!

IMPORTANT:
This library will output values above 100% and below 0% for humidity, that will allow you to calibrate the sensor if desired. It's recommended to trim the data between 0-100% before using.

WIRING DIAGRAM:

Thermistor:

[+5V]----------[10k resistor]-----(analog temp_pin)------[10k NTC]------------ [GROUND]

HR202 sensor:

[pulse_pin] -------- [10k resistor]-------(analog humidity_pin)----------[HR202]--------[pulse2_pin]
