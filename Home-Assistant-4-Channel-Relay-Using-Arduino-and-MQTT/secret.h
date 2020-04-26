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

const char* mqttClientId = "ClientId";                //MQTT Client id


/***************************************************
         OTA Hostname Settings
 **************************************************/

const char* otaHostName = "OTA Hostname";             //Arduino OTA Hostname


/***************************************************
       Home Assistant Topic Settings
 **************************************************/ 
char const * bedLightCommandTopic = "/house/room/bedlight/";                  // These are the MQTT Topic that will be used to manage the state of Relays 1 ~ 4
char const * backSideLightCommandTopic = "/house/room/backsidelight/";        // Feel free to replicate the line if you have more relay switch to control, but dont forget to increment the number suffix so as increase switch logics in loop()
char const * fanCommandTopic = "/house/room/fan/";
char const * frontLightCommandTopic = "/house/room/frontlight/";

char const * bedLightStateTopic = "/house/room/confirmbedlight/";           
char const * backSideLightStateTopic = "/house/room/confirmbacksidelight/";    
char const * fanStateTopic = "/house/room/confirmfan/";
char const * frontLightStateTopic = "/house/room/confirmfrontlight/";

char const * firmwareBuildNumberStateTopic = "/house/room/firmware/confirmbuildnumber/";
char const * firmwareUpdateCommandTopic = "/house/room/firmware/";
char const * firmwareUpdateStateTopic = "/house/room/confirmfirmware/";


/***************************************************
          Firmware URL
 **************************************************/ 
#define FIRMWARE_URL "http://www.example.com/Home-Assistant-4-Channel-Relay-With-Physical-Button-Control.ino.generic.bin"    // Enter the firmware URL location. Only http Protocol is supported. https not supported. Used for FOTA
