//////////////////////////////////////////////////////////// 
//             Secret Configuration                      //
////////////////////////////////////////////////////////// 


/***************************************************
          WiFi Settings
 **************************************************/
const char* ssid = "Your WiFi Network Name";
const char* password = "Your Wifi Password";


/***************************************************
          MQTT Server Settings
 **************************************************/
const char* mqtt_server = "xxx.xxx.xx.xxx";           //MQTT server ip address
const int mqttPort = xxxx;                            //MQTT broker port

const char* mqttUser = "Your MQTT Username";          //MQTT broker username
const char* mqttPassword = "Your MQTT Password";      //MQTT broker user password


/***************************************************
          Firmware URL
 **************************************************/ 
#define FIRMWARE_URL "http://www.example.com/Home-Assistant-4-Channel-Relay-With-Physical-Button-Control.ino.generic.bin"    // Enter the firmware URL location. Only http Protocol is supported. https not supported. Used for FOTA
