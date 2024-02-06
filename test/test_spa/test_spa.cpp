#include <Arduino.h>
#include <SpaIot.h>
#include <unity.h>

using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// UNITY FUNCTIONS
void setUp() {
  
}

void tearDown() {

}

void test_function_powerOn() {
  TEST_ASSERT_TRUE(spa.isPowerOn());
}

void test_function_bubble() {
  delay(2000);
  spa.setBubble(true);
  TEST_ASSERT_TRUE(spa.isBubbleOn());
  delay(2000);
  spa.setBubble(false);
}

void test_function_filter() {
  spa.setFilter(true);
  delay(2000);
  TEST_ASSERT_TRUE(spa.isFilterOn());
  delay(2000);
  spa.setFilter(false);
}

void test_function_heater() {
  spa.setHeater(true);
  delay(2000);
  TEST_ASSERT_TRUE(spa.isHeaterOn());
  delay(2000);
  spa.setHeater(false);
  TEST_ASSERT_FALSE(spa.isHeateron());
}

void runUnityTests() {
  UNITY_BEGIN();
  Serial.println("THIS FILE IS A UNIT TEST OF THE INTEX SPA SIMULATOR");
  Serial.println("START OF UNIT TEST");
  Serial.println("");
  spa.setPower(true);
  delay(500);
  RUN_TEST(test_function_powerOn);
  RUN_TEST(test_function_bubble);
  RUN_TEST(test_function_filter);
  RUN_TEST(test_function_heater);
  Serial.println("\nEND OF TEST");
  spa.setPower(false);
  Serial.println("SPA POWER OFF");
  Serial.println("");
  delay(8000);
  UNITY_END();
}

// PROGRAM
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
  spa.setPower(false);
}

void loop() {
  delay(2000);
  runUnityTests();
}
