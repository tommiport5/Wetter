/***************************************************************************
This is a webserver that shows humidity and temperature
 ***************************************************************************/

#include <Wire.h>
#include <SHT21.h>
#include "ServerWrapper.h"

#include "local.h"

const int sda_pin = D2;
const int scl_pin = D4;

SHT21 sht; // I2C

ServerWrapper server;

std::string WelcomePage = {
  "<html>"
  "<head>"
  "<title>Welcome to the TempHum server</title>"
  "</head>"
  "<body>"
  "<h1>Hi!</h1>"
  "<p>This is the webserver on the ESP8266 connected to the temperature and humidity server again.</p>"
  "</body>"
  "</html>"
};

void welcome(ServerWrapper *srv) {
  srv->send(200, "text/html", WelcomePage);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);    // time to get serial running
  Serial.println(F("SHT21 test"));

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  server.begin();
  server.answer("/welcome", welcome);

  // default settings
  Wire.begin(sda_pin, scl_pin);

  int SNo = sht.getSerialNumber(I2C_ADD);
  
  Serial.print("Serialnumber is: 0x"); Serial.println(SNo,16);
    Serial.println();
}


void loop() { 
  server.handleClient();
  MDNS.update();
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
