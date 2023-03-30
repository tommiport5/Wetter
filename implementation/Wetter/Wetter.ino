/***************************************************************************
  This is a library for the SHT21 humidity, temperature & pressure sensor

 Based on an example made by adafruit
  ----> http://www.adafruit.com/products/2650


  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SHT21.h>

const int sda_pin = D2;
const int scl_pin = D4;

SHT21 sht; // I2C

unsigned long delayTime = 1000;

void setup() {
    Serial.begin(115200);
    while(!Serial);    // time to get serial running
    Serial.println(F("SHT21 test"));

    unsigned status;
    
    // default settings
    Wire.begin(sda_pin, scl_pin);

    int SNo = sht.getSerialNumber(I2C_ADD);
   
    Serial.print("Serialnumber is: 0x"); Serial.println(SNo,16);
    delayTime = 1000;

    Serial.println();
}


void loop() { 
    printValues();
    delay(delayTime);
}


void printValues() {
    Serial.print("Temperature = ");
    Serial.print(sht.getTemperature());
    Serial.println(" °C");

    Serial.print("Humidity = ");
    Serial.print(sht.getHumidity());
    Serial.println(" %");

    Serial.println();
}
