#include <Arduino.h>
#include <SpaIot.h>
#include <unity.h>
#include <unity-config.h>

using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// UNITY FUNCTIONS
void setUp() {
  
}

void tearDown() {

}

void test_function_powerOn() {
    spa.setPower(true);
    TEST_ASSERT_TRUE(spa.isPowerOn());
}

void test_function_powerOff() {
    spa.setPower(false);
    TEST_ASSERT_FALSE(spa.isPowerOn());
}

void test_function_bubble() {
    delay(2000);
    spa.setBubble(true);
    TEST_ASSERT_TRUE(spa.isBubbleOn());
    delay(2000);
    spa.setBubble(false);
    TEST_ASSERT_FALSE(spa.isBubbleOn());
    }

    void test_function_filter() {
    spa.setFilter(true);
    delay(2000);
    TEST_ASSERT_TRUE(spa.isFilterOn());
    delay(2000);
    spa.setFilter(false);
    TEST_ASSERT_FALSE(spa.isFilterOn());
}

void test_function_heater() {
    spa.setHeater(true);
    delay(2000);
    TEST_ASSERT_TRUE(spa.isHeaterOn());
    delay(2000);
    spa.setHeater(false);
    TEST_ASSERT_FALSE(spa.isHeaterOn());
}

void runUnityTests() {
    UNITY_BEGIN();
    delay(500);
    RUN_TEST(test_function_powerOn);
    RUN_TEST(test_function_bubble);
    RUN_TEST(test_function_filter);
    RUN_TEST(test_function_heater);
    RUN_TEST(test_function_powerOff);
    delay(8000);
    UNITY_END();
}

// PROGRAM
void setup() {
    Serial.begin(115200);

    spa.begin();
    while(spa.isOpen() == false) {
        delay(2000);
    }
    runUnityTests();
}

void loop() {
    // DO NOTHING
}
