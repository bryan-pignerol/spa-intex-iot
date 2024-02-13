#include <Arduino.h>
#include <SpaIot.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <unity.h>
#include <unity_config.h>

using namespace SpaIot;

/// VARIABLES
// WIFI
const char* ssid = "Yamaworld";
const char* password = "123457ab";

// MQTT
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char* mqttUsername = "";
const char* mqttPassword = "";
char* topicPower = "espbryan/esp/power";
char* topicBubble = "espbryan/esp/bubble";
char* topicFilter = "espbryan/esp/filter";
char* topicHeater = "espbryan/esp/heater";
String messageTemp;

/// OBJECTS
ControlPanel spa ("SPAIOT32SSP");
WiFiClient espClient;
PubSubClient client(espClient);

/// FONCTIONS
void connect_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}

void connect_mqtt() {
  client.setServer(mqttServer, mqttPort);
  while(!client.connected()) {
    String clientId = "esp32-client-";
    if(client.connect(clientId.c_str(), mqttUsername, mqttPassword)) {
    } else {
      delay(100);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  messageTemp = "";
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }
  Serial.println(messageTemp);
}

/// UNITY
void setUp() {

}

void tearDown() {

}

void test_function_mqttConnected() {
  TEST_ASSERT_TRUE(client.connected());
  delay(1000);
}

void test_function_powerOnMqtt() {
  callback(topicPower, (byte*)"turnOn", 6);
  if(messageTemp == "turnOn") {
    spa.setPower(true);
  }
  TEST_ASSERT_TRUE(spa.isPowerOn());
  delay(1000);
}

void test_function_bubbleOnMqtt() {
  callback(topicBubble, (byte*)"enableBubble", 12);
  if(messageTemp == "enableBubble") {
    spa.setBubble(true);
  }
  TEST_ASSERT_TRUE(spa.isBubbleOn());
  delay(1000);
}

void test_function_bubbleOffMqtt() {
  callback(topicBubble, (byte*)"disableBubble", 13);
  if(messageTemp == "disableBubble") {
    spa.setBubble(false);
  }
  TEST_ASSERT_FALSE(spa.isBubbleOn());
  delay(1000);
}

void test_function_filterOnMqtt() {
  callback(topicFilter, (byte*)"enableFilter", 12);
  if(messageTemp == "enableFilter") {
    spa.setFilter(true);
  }
  TEST_ASSERT_TRUE(spa.isFilterOn());
  delay(1000);
}

void test_function_filterOffMqtt() {
  callback(topicFilter, (byte*)"disableFilter", 13);
  if(messageTemp == "disableFilter") {
    spa.setFilter(false);
  }
  TEST_ASSERT_FALSE(spa.isFilterOn());
  delay(1000);
}

void test_function_heaterOnMqtt() {
  callback(topicHeater, (byte*)"enableHeater", 12);
  if(messageTemp == "enableHeater") {
    spa.setHeater(true);
  }
  TEST_ASSERT_TRUE(spa.isHeaterOn());
  delay(1000);
}

void test_function_heaterOffMqtt() {
  callback(topicHeater, (byte*)"disableHeater", 13);
  if(messageTemp == "disableHeater") {
    spa.setHeater(false);
  }
  TEST_ASSERT_FALSE(spa.isHeaterOn());
  delay(1000);
}

void test_function_powerOffMqtt() {
  callback(topicPower, (byte*)"turnOff", 7);
  if(messageTemp == "turnOff") {
    spa.setPower(false);
  }
  TEST_ASSERT_FALSE(spa.isPowerOn());
  delay(1000);
}

void runUnityTests() {
  UNITY_BEGIN();
  RUN_TEST(test_function_mqttConnected);
  client.publish(topicPower, "turnOn");
  delay(1000);
  RUN_TEST(test_function_powerOnMqtt);
  delay(1000);
  client.publish(topicBubble, "enableBubble");
  delay(1000);
  RUN_TEST(test_function_bubbleOnMqtt);
  client.publish(topicBubble, "disableBubble");
  delay(1000);
  RUN_TEST(test_function_bubbleOffMqtt);
  client.publish(topicFilter, "enableFilter");
  delay(1000);
  RUN_TEST(test_function_filterOnMqtt);
  client.publish(topicFilter, "disableFilter");
  delay(1000);
  RUN_TEST(test_function_filterOffMqtt);
  client.publish(topicHeater, "enableHeater");
  delay(1000);
  RUN_TEST(test_function_heaterOnMqtt);
  client.publish(topicHeater, "disableHeater");
  delay(1000);
  RUN_TEST(test_function_heaterOffMqtt);
  client.publish(topicPower, "turnOff");
  delay(1000);
  RUN_TEST(test_function_powerOffMqtt);
  delay(500);
  UNITY_END();
}

/// FONCTIONS SYSTEME
void setup() {
  Serial.begin(115200);

  spa.begin();
  while(spa.isOpen() == false) {
    delay(2000);
  }
  spa.setPower(false);
  delay(1000);
  connect_wifi();
  connect_mqtt();
  client.setCallback(callback);
  client.subscribe(topicPower);
  client.subscribe(topicBubble);
  client.subscribe(topicFilter); 
  client.subscribe(topicHeater);
  runUnityTests();
}

void loop() {

}
