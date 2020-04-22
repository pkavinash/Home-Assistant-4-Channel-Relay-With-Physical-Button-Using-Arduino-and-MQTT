
# Home-Assistant-4-Channel-Relay-With-Physical-Button-Using-Arduino-and-MQTT
4 channel relay with physical button control, implemented using Arduino, NodeMCU, MQTT and Home Assistant.  

## What it Does?
1) 4 Channel Relay control with Home Assistant app/desktop  
2) If you perform ON/OFF with Physical/Push button switch, the status gets updated on Home Assistant app/desktop  
3) If Internet is not available, you can still operate Relay with offline physical switch

## Requirements
1) [NodeMCU](http://s.click.aliexpress.com/e/nlefJ4PI)
2) [4 Channel Relay Module](http://s.click.aliexpress.com/e/eK05ynRS)
3) [Home Assistant App](https://play.google.com/store/apps/details?id=io.homeassistant.companion.android&hl=en)

## Installation

 - Open <code>secret.h</code> and change Bynk Auth code, Wifi settings, server settings and few other parameters as per your project requirement.
 - Open <code>settings.h</code> - Usually you don't need to change any values here, but if you need any customization feel free play with it.


## Hardware Connection

### NodeMCU to 4 Channel Relay Module Connection
D0 or 16 to IN1</br>
D1 or 5 to IN2</br>
D2 or 4 to IN3</br>
D3 or 0 to IN4</br>
VV to VCC</br>
GND to GND</br>

### NodeMCU Connection for Switch Actions (NodeMCU to NodeMCU)
D4 or 2 to GND (in NodeMCU) </br>
D5 or 14 to GND (in NodeMCU) </br>
D6 or 12 to GND (in NodeMCU) </br>
D7 or 13 to GND (in NodeMCU) </br>


## Software Setup

 - Download and install the Home Assistant  App for iOS or Android.
 - Download this repo and copy the files in to your sketches directory. Open the sketch in Arduino IDE.
 - Go to the <code>settings.h</code> tab. This is where all the customisable settings are. You should be able to change almost everything from there before compiling.
 - Go to the <code>secret.h</code> tab. Here you change Wifi settings, server settings and few other parameters as per your project requirement.
 

