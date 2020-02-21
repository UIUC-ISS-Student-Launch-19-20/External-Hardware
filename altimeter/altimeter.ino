/**************************************************************************/
/*!
    @file     Adafruit_MPL3115A2.cpp
    @author   K.Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    Example for the MPL3115A2 barometric pressure sensor

    This is a library for the Adafruit MPL3115A2 breakout
    ----> https://www.adafruit.com/products/1893

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

// Power by connecting Vin to 3-5V, GND to GND
// Uses I2C - connect SCL to the SCL pin, SDA to SDA pin
// See the Wire tutorial for pinouts for each Arduino
// http://arduino.cc/en/reference/wire
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit_MPL3115A2 test!"); Serial.println("");
}

void loop() {
  if (! baro.begin()) {
    Serial.println("Couldn't find sensor");
    return;
  }
  
  float pascals = baro.getPressure();
  float altm = baro.getAltitude();
  float tempC = baro.getTemperature();

  Serial.print("Pressure: "); Serial.print(pascals); Serial.println(" pascals");

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" C");
  
  Serial.print("Altitude: "); Serial.print(altm); Serial.println(" meters");

  Serial.println("");

  delay(250);
}
