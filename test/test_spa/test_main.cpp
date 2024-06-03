#include <Arduino.h>
#include <SpaIot.h>
#include <unity.h>
#include <unity_config.h>

using namespace SpaIot;

// GLOBAL VARIABLES
ControlPanel spa ("SPAIOT32SSP"); // SPAIOT32SSP

// UNITY FUNCTIONS
void setUp() {
  
}

void tearDown() {

}

void test_function_powerOn() { // Test d'allumage du spa
    spa.setPower(true);
    TEST_ASSERT_TRUE(spa.isPowerOn());
}

void test_function_powerOff() { // Test d'extinction du spa
    spa.setPower(false);
    TEST_ASSERT_FALSE(spa.isPowerOn());
}

void test_function_bubble() { // Test de l'activation des bulles
    delay(2000);
    spa.setBubble(true);
    TEST_ASSERT_TRUE(spa.isBubbleOn());
    delay(2000);
    spa.setBubble(false);
    TEST_ASSERT_FALSE(spa.isBubbleOn());
}

void test_function_filter() { // Test de l'activation du filtre
    spa.setFilter(true);
    delay(2000);
    TEST_ASSERT_TRUE(spa.isFilterOn());
    delay(2000);
    spa.setFilter(false);
    TEST_ASSERT_FALSE(spa.isFilterOn());
}

void test_function_heater() { // Test de l'activation du chauffage
    spa.setHeater(true);
    delay(2000);
    TEST_ASSERT_TRUE(spa.isHeaterOn());
    delay(2000);
    spa.setHeater(false);
    TEST_ASSERT_FALSE(spa.isHeaterOn());
}

void runUnityTests() { // Fonction de lancement des tests unitaires
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
    while(spa.isOpen() == false) { // Attente de l'ouverture du spa
        delay(2000);
    }
    runUnityTests(); // Lancement des tests unitaires
}

void loop() {
    // DO NOTHING
}
