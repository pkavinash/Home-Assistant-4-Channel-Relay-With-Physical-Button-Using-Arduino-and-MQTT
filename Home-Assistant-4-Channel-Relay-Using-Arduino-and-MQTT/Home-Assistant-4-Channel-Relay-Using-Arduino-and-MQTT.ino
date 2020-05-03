//4 Channel Relay Switch with physical button control using MQTT and Home Assistant with OTA Support
//
//Requires PubSubClient found here: https://github.com/knolleary/pubsubclient
//
//ESP8266 Simple MQTT switch controller

//NodeMCU to 4 Channel Relay Module Connection
//D0 or 16 to IN1
//D1 or 5 to IN2
//D2 or 4 to IN3
//D3 or 0 to IN4
//VV to VCC
//GND to GND

//NodeMCU Connection for Switch Actions (NodeMCU to NodeMCU)
//D4 or 2 to GND (in NodeMCU)
//D5 or 14 to GND (in NodeMCU)
//D6 or 12 to GND (in NodeMCU)
//D7 or 13 to GND (in NodeMCU)

#include "settings.h"
//#include "secret.h"                   // <<--- UNCOMMENT this before you use and change values on config.h tab
#include "my_secret.h"                  // <<--- COMMENT-OUT or REMOVE this line before you use. This is my personal settings.
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

void callback(char * topic, byte * payload, unsigned int length);

int relay1State = LOW;
int relay2State = LOW;
int relay3State = LOW;
int relay4State = LOW;

int pushButton1State = LOW;
int pushButton2State = LOW;
int pushButton3State = LOW;
int pushButton4State = LOW;

WiFiClient wifiClient;
PubSubClient client(mqtt_server, mqttPort, callback, wifiClient);

void setup() {
  //initialize the switch as an output and set to LOW (off)
  pinMode(RELAY_PIN_1, OUTPUT);                 // Relay Switch 1
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, HIGH);

  pinMode(RELAY_PIN_2, OUTPUT);                 // Relay Switch 2
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_2, HIGH);

  pinMode(RELAY_PIN_3, OUTPUT);                 // Relay Switch 3
  pinMode(PUSH_BUTTON_3, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_3, HIGH);

  pinMode(RELAY_PIN_4, OUTPUT);                 // Relay Switch 4
  pinMode(PUSH_BUTTON_4, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_4, HIGH);

  ArduinoOTA.setHostname(otaHostName);          // A name given to your ESP8266 module when discovering it as a port in ARDUINO IDE
  ArduinoOTA.begin();                           // OTA initialization
  
  Serial.begin(115200);                         // Start the serial line for debugging
  delay(100);

  WiFi.begin(ssid, password);                   // Start wifi subsystem  
  reconnectWifi();                              // Attempt to connect to the WIFI network and then connect to the MQTT server
  delay(2000);                                  // Wait a bit before starting the main loop
}

void loop() {  
  if (WiFi.status() != WL_CONNECTED) {          // Reconnect if connection is lost
    reconnectWifi();
  } else if (!client.connected()) {
    reconnectMQTT();
  } else {    
    checkPhysicalButton(); 
    client.loop();                              // Maintain MQTT connection   
    delay(10);                                  // MUST delay to allow ESP8266 WIFI functions to run
    ArduinoOTA.handle();
  }
}

void callback(char * topic, byte * payload, unsigned int length) {
  String topicStr = topic;                                // Convert topic to string to make it easier to work with
  Serial.println("Callback update.");
  Serial.println("Topic: ");
  Serial.println(topicStr);                               // Note:  the "topic" value gets overwritten everytime it receives confirmation (callback) message from MQTT

  if (topicStr == bedLightCommandTopic) {    
    if (payload[0] == '1') {                              // Turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_1, LOW);
      client.publish(bedLightStateTopic, "1");
    }    
    else if (payload[0] == '0') {                         // Turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_1, HIGH);
      client.publish(bedLightStateTopic, "0");
    }
  } else if (topicStr == backSideLightCommandTopic) {
    if (payload[0] == '1') {                              // Turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_2, LOW);
      client.publish(backSideLightStateTopic, "1");
    }
    else if (payload[0] == '0') {                         // Turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_2, HIGH);
      client.publish(backSideLightStateTopic, "0");
    }
  } else if (topicStr == fanCommandTopic) {
    if (payload[0] == '1') {                              // Turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_3, LOW);
      client.publish(fanStateTopic, "1");
    }
    else if (payload[0] == '0') {                         // Turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_3, HIGH);
      client.publish(fanStateTopic, "0");
    }
  } else if (topicStr == frontLightCommandTopic) {
    if (payload[0] == '1') {                              // Turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_4, LOW);
      client.publish(frontLightStateTopic, "1");
    }
    else if (payload[0] == '0') {                         // Turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
      digitalWrite(RELAY_PIN_4, HIGH);
      client.publish(frontLightStateTopic, "0");
    }
  } else if (topicStr == firmwareUpdateCommandTopic) {
    Serial.println("Firmware update calling ");
    if (payload[0] == '1') {                              // Turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
      checkforupdate();
    } else if (payload[0] == '0') {                       // Turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
      Serial.println("Firmware switch off ");
    }
  }
  publishData(BUILD_NUMBER);                              // Sending message to MQTT server to set build number in home assistant UI
}

void publishData(int p_buildNumber) {                                 // function called to publish the temperature and the humidity  
  StaticJsonDocument < 200 > jsonDocument;                            // create a JSON object  
  jsonDocument["buildNumber"] = (String) p_buildNumber;               // INFO: the data must be converted into a string; a problem occurs when using floats...
  char data[200];
  serializeJson(jsonDocument, data);
  client.publish(firmwareBuildNumberStateTopic, data, true);          //Publishing data to MQTT server as Json
  yield();
}

void checkPhysicalButton() {
  if (digitalRead(PUSH_BUTTON_1) == 0) {
    if (pushButton1State != LOW) {                        // PushButton1State is used to avoid sequential toggles
      relay1State = !relay1State;                         // Toggle Relay state
      digitalWrite(RELAY_PIN_1, relay1State);
      if (relay1State == LOW) {
        client.publish(bedLightStateTopic, "1");
      } else {
        client.publish(bedLightStateTopic, "0");
      }
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_2) == 0) {    
    if (pushButton2State != LOW) {                        // PushButton2State is used to avoid sequential toggles      
      relay2State = !relay2State;                         // Toggle Relay state
      digitalWrite(RELAY_PIN_2, relay2State);
      if (relay2State == LOW) {
        client.publish(backSideLightStateTopic, "1");
      } else {
        client.publish(backSideLightStateTopic, "0");
      }
    }
    pushButton2State = LOW;
  } else {
    pushButton2State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_3) == 0) {    
    if (pushButton3State != LOW) {                        // PushButton3State is used to avoid sequential toggles      
      relay3State = !relay3State;                         // Toggle Relay state
      digitalWrite(RELAY_PIN_3, relay3State);
      if (relay3State == LOW) {
        client.publish(fanStateTopic, "1");
      } else {
        client.publish(fanStateTopic, "0");
      }
    }
    pushButton3State = LOW;
  } else {
    pushButton3State = HIGH;
  }

  if (digitalRead(PUSH_BUTTON_4) == 0) {    
    if (pushButton4State != LOW) {                        // PushButton4State is used to avoid sequential toggles      
      relay4State = !relay4State;                         // Toggle Relay state
      digitalWrite(RELAY_PIN_4, relay4State);
      if (relay4State == LOW) {
        client.publish(frontLightStateTopic, "1");
      } else {
        client.publish(frontLightStateTopic, "0");
      }
    }
    pushButton4State = LOW;
  } else {
    pushButton4State = HIGH;
  }
}

void reconnectWifi() {
  Serial.println("");
  Serial.println("Wifi status = ");
  Serial.println(WiFi.status());  
  if (WiFi.status() != WL_CONNECTED) {                    // Attempt to connect to the wifi if connection is lost
    Serial.println("Connecting to ");
    Serial.println(ssid);
        
    while (WiFi.status() != WL_CONNECTED) {               // Loop while we wait for connection
      checkPhysicalButton();
      delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    reconnectMQTT();
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void reconnectMQTT() {
  delay(1000);  
  if (WiFi.status() == WL_CONNECTED) {                    // Make sure we are connected to WIFI before attemping to reconnect to MQTT    
    while (!client.connected()) {                         // Loop until we're reconnected to the MQTT server
      checkPhysicalButton();
      Serial.println("Attempting MQTT connection...");      
      String clientName;                                  // Generate client name based on MAC address and last 8 bits of microsecond counter
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);      
       
      if (client.connect(mqttClientId, mqttUser, mqttPassword)) {         // Delete "mqtt_username", and "mqtt_password" here if you are not using any
        Serial.println("\tMQTT Connected");
        client.subscribe(bedLightCommandTopic);                           // If connected, subscribe to the topic(s) we want to be notified about
        client.subscribe(backSideLightCommandTopic);
        client.subscribe(fanCommandTopic);
        client.subscribe(frontLightCommandTopic);                         // Do not forget to replicate the above line if you will have more than the above number of relay switches
        client.subscribe(firmwareUpdateCommandTopic);
        client.publish(firmwareUpdateStateTopic, "0");                    // Sending message to MQTT server to turn off MQTT firmware upgrade button if its on
        publishData(BUILD_NUMBER);                                        // Sending message to MQTT server to set build number in home assistant UI
      }
      else {
        Serial.println("\tFailed.");
        checkPhysicalButton();
      }
    }
  } else {
    Serial.println("Wifi is not connected");
  }
}

void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void checkforupdate() {
  Serial.println("OTA Update Request Received");
  Serial.println("Firmware URL: ");
  Serial.println(FIRMWARE_URL);

  HTTPClient httpClient;
  httpClient.begin(FIRMWARE_URL);
  int httpCode = httpClient.GET();

  if (httpCode == 200) {
    Serial.println("Update file found, starting update");    
//    ESPhttpUpdate.onStart(update_started);                             // Add optional callback notifiers if necessary
//    ESPhttpUpdate.onEnd(update_finished);
//    ESPhttpUpdate.onProgress(update_progress);
//    ESPhttpUpdate.onError(update_error);
    t_httpUpdate_return ret = ESPhttpUpdate.update(FIRMWARE_URL);

    switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("[update] Update failed.");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[update] Update no Update.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[update] Update ok.");                            // May not called we reboot the ESP
      break;
    }
  } else {
    publishData(BUILD_NUMBER);
    client.publish(firmwareUpdateStateTopic , "0");                     // Sending message to MQTT server to turn off MQTT firmware upgrade button if its on
    Serial.println("Firmware check failed, got HTTP response code ");
    Serial.println(httpCode);
  }
  httpClient.end();
}

String macToStr(const uint8_t * mac) {                                  // Generate unique name from MAC addr
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5) {
      result += ':';
    }
  }
  return result;
}
