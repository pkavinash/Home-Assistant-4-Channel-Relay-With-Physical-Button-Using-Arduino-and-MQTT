
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

 - Open <code>secret.h</code> and change Wifi settings, server settings and few other parameters as per your project requirement.
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
homeassistant:
  customize: 
      switch.bed_light:
        icon: mdi:ceiling-light 
        assumed_state: false
      switch.backside_light:
        icon: mdi:lightbulb 
        assumed_state: false
      switch.front_light:
        icon: mdi:lightbulb-outline
        assumed_state: false
      switch.fan:
        icon: mdi:fan
        assumed_state: false
      switch.room_firmware_update:
        assumed_state: false

switch 1:
  - platform: mqtt
    name: "Bed Light"
    state_topic: "/house/room/confirmbedlight/"
    command_topic: "/house/room/bedlight/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0

switch 2:
  - platform: mqtt
    name: "Backside Light"
    state_topic: "/house/room/confirmbacksidelight/"
    command_topic: "/house/room/backsidelight/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0

switch 3:
  - platform: mqtt
    name: "Fan"
    state_topic: "/house/room/confirmfan/"
    command_topic: "/house/room/fan/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0

switch 4:
  - platform: mqtt
    name: "Front Light"
    state_topic: "/house/room/confirmfrontlight/"
    command_topic: "/house/room/frontlight/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0

  - platform: mqtt
    name: "Room Firmware Update"
    state_topic: "/house/room/confirmfirmware/"
    command_topic: "/house/room/firmware/"
    payload_on: "1"
    payload_off: "0"
    optimistic: true
    qos: 0 
```

### Add in sensors.yaml
```python
  - platform: mqtt
    name: "Room Build Number"
    state_topic: "/house/room/firmware/confirmbuildnumber/"
    value_template: '{{ value_json.buildNumber }}'
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
 
## Screenshot
<img src="/Images/1.jpg" width="" height="" style="max-width:100%;"></br>
<img src="/Images/2.jpg" width="" height="" style="max-width:100%;"></br>
<img src="/Images/3.png" width="350" height="" style="max-width:100%;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
<img src="/Images/4.png" width="350" height="" style="max-width:100%;">
