#include <Arduino.h>
#include <SpaIot.h>

// NAMESPACE
using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// VARIABLES
String command;

// FUNCTIONS
void executeCommand(String command) {
  if(command.startsWith("/help")) { // SHOW ALL COMMANDS
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
  }

  else if(command.startsWith("/turnOn")) {
    spa.setPower(true); // Turn on the spa
    Serial.println("SPA POWER ON");
    Serial.println("");
  }

  else if(command.startsWith("/turnOff")) {
    spa.setPower(false); // Turn off the spa
    Serial.println("SPA POWER OFF");
    Serial.println("");
  }

  else if(command.startsWith("/enableBubble")) {
    spa.setBubble(true); // Enable the bubbles
    Serial.println("SPA BUBBLE ON");
    Serial.println("");
  }

  else if(command.startsWith("/disableBubble")) {
    spa.setBubble(false); // Disable the bubbles
    Serial.println("SPA BUBBLE OFF");
    Serial.println("");
  }

  else if(command.startsWith("/enableFilter")) {
    spa.setFilter(true);
    Serial.println("SPA FILTER ON");
    Serial.println("");
  }

  else if(command.startsWith("/disableFilter")) {
    spa.setFilter(false);
    Serial.println("SPA FILTER OFF");
    Serial.println("");
  }

  else if(command.startsWith("/enableHeater")) {
    spa.setHeater(true);
    Serial.println("SPA HEATER ON");
    Serial.println("");
  }

  else if(command.startsWith("/disableHeater")) {
    spa.setHeater(false);
    Serial.println("SPA HEATER OFF");
    Serial.println("");
  }

  else if(command.startsWith("/showWaterTemp")) {
    Serial.print("WATER TEMPERATURE : ");
    Serial.print(spa.waterTemp());
    Serial.println(" C");
    Serial.println("");
  }

  else if(command.startsWith("/test")) {
    spa.setPower(true);
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

    spa.setPower(false);
    Serial.println("SPA POWER OFF");
    delay(5000);
    Serial.println("");
  }

  else {
    Serial.println("COMMAND NOT FOUND");
  }
}

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
  // ENTER COMMAND
  while(Serial.available()) {
    char inChar = (char)Serial.read();
    if(inChar != '\r') {
      command += inChar;
      Serial.print(inChar);
    }
    if (inChar == '\n') {
      Serial.print("Commande reçue : ");
      Serial.print(command);
      executeCommand(command);
      command = "";
    }
  }
}