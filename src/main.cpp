#include <Arduino.h>
#include <SpaIot.h>

// NAMESPACE
using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// FUNCTIONS


void setup() {
  Serial.begin(115200);
  Serial.println("SPA INTEX IOT BY BRYAN PIGNEROL");

  spa.begin();
  while(spa.isOpen() == false) {
    Serial.println("SPA NOT OPENED");
    delay(2000);
  }
  Serial.println("SPA OPENED");
}

void loop() {
  spa.setPower(true); // Turn on the spa
  Serial.println("SPA POWER ON");
  delay(2000);

  // BUBBLE
  spa.setBubble(true);
  Serial.println("SPA BUBBLE ON");
  delay(5000);
  spa.setBubble(false);
  Serial.println("SPA BUBBLE OFF");

  // FILTER
  spa.setFilter(true);
  Serial.println("SPA FILTER ON");
  delay(5000);
  spa.setFilter(false);
  Serial.println("SPA FILTER OFF");

  // HEATER
  spa.setHeater(true);
  Serial.println("SPA HEATER ON");
  delay(5000);
  spa.setHeater(false);
  Serial.println("SPA HEATER OFF");

  spa.setPower(false); // Turn off the spa
  delay(10000);
}