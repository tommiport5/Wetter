/***************************************************************************
This is a webserver that shows humidity and temperature
 ***************************************************************************/

#include <Wire.h>
#include <SHT21.h>
#include "ServerWrapper.h"
#include "StringTpl.h"
#include <utility>
#include <cstdlib>

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
const StringTpl TempPage = StringTpl(
  "<html>"
  "<head>"
  "<meta charset='utf-8'>"
  "<meta http-equiv='refresh' content='5' />"
  "<title>Temperatur und Feuchtigkeit</title>"
  "</head>"
  "<body>"
  "<h1>Hallo!</h1>"
  "<p>Die Temperatur beträgt $temp °C und die Feuchtigkeit $hum % (Messung #$count).</p>"
  "</body>"
  "</html>"

);

void welcome(ServerWrapper *srv) {
  srv->send(200, "text/html", WelcomePage);
}

StringTpl::map_t &&buildDataMap(StringTpl::map_t &dm) {
  StringTpl::map_t loc;
  static int count = 1;
  char tmp[16];
  loc["temp"] = sht.getTemperature();
  loc["hum"] = sht.getHumidity();
  loc["count"] = itoa(count++, tmp, 10);
  std::swap(loc, dm);
  return move(dm);
}

void temperature(ServerWrapper *srv) {
  StringTpl::map_t DataMap;
  srv->send(200, "text/html", TempPage.safe_substitute(buildDataMap(DataMap)));
}

void setup() {
  Serial.begin(115200);
  while(!Serial);    // time to get serial running
  Serial.println(F("SHT21 test"));

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  server.begin();
  server.answer("/welcome", welcome);
  server.answer("/temperature", temperature);

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

