# Shockless
The DIY Smart Plug

ESP8266 IoT based smart plug using MQTT and Node-RED
Protecting plug from accidental shocking with sensing from PIR sensor, and monitoring power usage with PZEM 004-T

# Team Member
- Hakim
- Leo
- Fajar
- Bagus

# Requirements
- LOLIN D1 mini 
- PIR Sensor
- PZEM 004-T

Software
- Arduino IDE
- Node-JS
- Node-RED
- MQTT Mosquitto

Arduino Library
- Protothread (https://gitlab.com/airbornemint/arduino-protothreads)
- PZEM Library (https://github.com/mandulaj/PZEM-004T-v30)
- EspMQTTClient (https://github.com/plapointe6/EspMQTTClient)
- ESP8266 Basic Library, import it from board manager (https://arduino.esp8266.com/stable/package_esp8266com_index.json)


# Wiring Diagram

![Relay and PIR Wiring Diagram](https://user-images.githubusercontent.com/107752934/208443310-2d24a526-efe0-4c12-9a86-572453bcf70d.png)
![PZEM Wiring Diagram](https://user-images.githubusercontent.com/107752934/208443615-71dbae15-1b80-40bc-8f4d-3f62b595b41f.png)

# Installation
1. Install Node-js first (https://nodejs.dev/learn/how-to-install-nodejs)
2. Install Node-red (https://nodered.org/docs/getting-started/local)
3. Install MQTT Broker (https://mosquitto.org/)
4. Import code from this source code for node-red
5. and change arduino code according your MQTT broker adress


# Next Goal
- Adding wifi setting and login page
- Integrating device power with the power plug
- Reduce footprint of the smart plug size
