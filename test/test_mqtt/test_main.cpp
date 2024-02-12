#include <Arduino.h>
#include <SpaIot.h>
#include <WiFi.h>
#include <unity.h>
#include <unity_config.h>

/// VARIABLES
// WIFI
const char* ssid = "Yamaworld";
const char* password = "123457ab";

// MQTT
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char* mqttUsername = "";
const char* mqttPassword = "";
const char* topicBubble = "espbryan/esp/bubble";
String messageTemp;

/// OBJECTS
WiFiClient espClient;
PubSubClient client(espClient);

/// FONCTIONS
void connect_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nCONNECTING");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nCONNECTED TO THE WIFI NETWORK");
}

void connect_mqtt() {
  client.setServer(mqttServer, mqttPort);
  Serial.print("MQTT CONNECTING");
  while(!client.connected()) {
    String clientId = "esp32-client-";
    Serial.print(".");
    if(client.connect(clientId.c_str(), mqttUsername, mqttPassword)) {
      Serial.println("\nCONNECTED TO THE MQTT");
    } else {
      delay(100);
    }
  }
  Serial.println();
}

void callback(char* topic, byte* payload, unsigned int length) {
    
}

/// UNITY

/// FONCTIONS SYSTEME
void setup() {
  Serial.begin(115200);
  delay(1000);
  connect_wifi();
  connect_mqtt();
  client.setCallback(callback);
}
