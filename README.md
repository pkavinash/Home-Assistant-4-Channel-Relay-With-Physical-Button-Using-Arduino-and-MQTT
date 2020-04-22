
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

## Home Assistant Configuration

### Add in configuration.yaml
```python
switch 1:
  - platform: mqtt
    name: "MQTT Switch 1"
    state_topic: "/house/switchConfirm1/"
    command_topic: "/house/switch1/"
    payload_on: "1"
    payload_off: "0"
    qos: 0
    retain: true 
    
switch 2:
  - platform: mqtt
    name: "MQTT Switch 2"
    state_topic: "/house/switchConfirm2/"
    command_topic: "/house/switch2/"
    payload_on: "1"
    payload_off: "0"
    qos: 0
    retain: true
    
switch 3:
  - platform: mqtt
    name: "MQTT Switch 3"
    state_topic: "/house/switchConfirm3/"
    command_topic: "/house/switch3/"
    payload_on: "1"
    payload_off: "0"
    qos: 0
    retain: true
    
switch 4:
  - platform: mqtt
    name: "MQTT Switch 4"
    state_topic: "/house/switchConfirm4/"
    command_topic: "/house/switch4/"
    payload_on: "1"
    payload_off: "0"
    qos: 0
    retain: true

  - platform: mqtt
    name: "MQTT Firmware Update"
    state_topic: "/house/switch/Confirmfirmware/"
    command_topic: "/house/switch/firmware/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0    
```

### Add in sensor.yaml
```python
  - platform: mqtt
    name: "Build Number"
    state_topic: "/house/switch/firmware/buildnumber/"
    qos: 0
```

### Add in groups.yaml
```python
  sensors_mqtt_group:
  name: Build Number
  entities:
    - sensor.build_number
```

### Add in automations.yaml
#Add this if you want to use automation</br>
#Example code is shown for only 1 switch</br>
```python
- id: TurnOn
  alias: Turn On Switch
  trigger:
  - at: '21:50:00'
    platform: time
  action:
  - entity_id: switch.mqtt_switch_1
    service: switch.toggle
```

## Software Setup

 - Download and install the Home Assistant  App for iOS or Android.
 - Download this repo and copy the files in to your sketches directory. Open the sketch in Arduino IDE.
 - Go to the <code>settings.h</code> tab. This is where all the customisable settings are. You should be able to change almost everything from there before compiling.
 - Go to the <code>secret.h</code> tab. Here you change Wifi settings, server settings and few other parameters as per your project requirement.
 

