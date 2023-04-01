/***************************************************************************
This is a webserver that shows humidity and temperature
 ***************************************************************************/

#include <Wire.h>
#include <SHT21.h>
#include "ServerWrapper.h"


const int sda_pin = D2;
const int scl_pin = D4;

SHT21 sht; // I2C

unsigned long delayTime = 1000;

extern int demo();

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
    demo();
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
