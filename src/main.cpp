#include <Arduino.h>
#include <SpaIot.h>

// NAMESPACE
using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// VARIABLES
String command;

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
  Serial.println("");
}

void loop() {
  command = "";

  // ENTER COMMAND
  // Serial.println("ENTER COMMAND");
  if(Serial.available()) {
    command = Serial.readStringUntil('\n');
    Serial.println(command);
  }

  if(command == "/help") { // SHOW ALL COMMANDS
    Serial.println("HELP");
    Serial.println("/help : show this help");
    Serial.println("/turnOn : Turn on the SPA");
    Serial.println("/turnOff : Turn off the SPA");
    Serial.println("/enableBubble : Enable the bubbles");
    Serial.println("/disableBubble : Disable the bubbles");
    Serial.println("/enableFilter : Enable the filter");
    Serial.println("/disableFilter : Disable the filter");
    Serial.println("/enableHeater : Enable the heater");
    Serial.println("/disableHeater : Disable the heater");
    Serial.println("/showWaterTemp : Show the water temperature");
    Serial.println("");
    delay(2000);
  }

  else if(command == "/turnOn") {
    spa.setPower(true); // Turn on the spa
    Serial.println("SPA POWER ON");
    delay(2000);
  }

  else if(command == "/turnOff") {
    spa.setPower(false); // Turn off the spa
    Serial.println("SPA POWER OFF");
    delay(2000);
  }

  else if(command == "/enableBubble") {
    spa.setBubble(true); // Enable the bubbles
    Serial.println("SPA BUBBLE ON");
    delay(2000);
  }

  else if(command == "/disableBubble") {
    spa.setBubble(false); // Disable the bubbles
    Serial.println("SPA BUBBLE OFF");
    delay(2000);
  }

  /* FILTER
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
  Serial.println("SPA HEATER OFF"); */
}