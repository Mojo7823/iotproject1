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

Node-Red Library
- node-red dashboard (https://flows.nodered.org/node/node-red-dashboard)

Demonstration
1. Child Lock : https://photos.app.goo.gl/yetZTeskmpnJDQRK6
2. Web UI Test : https://photos.app.goo.gl/uKftXLBL7Zmyzr1g9


# Node-RED User Interface
![Node-Red Dashboard](https://user-images.githubusercontent.com/107752934/208565733-f364b671-417c-46db-8cbe-633b63e01769.png)


# Wiring

## Pin Used
| ---- | ---- | ----   |
| D1 Mini PIN | Pin | Description |
| D2 | Relay IN | Relay Input   |
| D4 | PIR Out | Pir Sensor Output   |
| D5 | LED RED | (Optional) LED Lock Status   |
| D6 | LED GREEN | (Optional) LED Lock Status   |
| D7 | PZEM TX | PZEM 004-T TX PIN   |
| D8 | PZEM RX | PZEM 004-T RX PIN   |

## Wiring Diagram
![Relay and PIR Wiring Diagram](https://user-images.githubusercontent.com/107752934/208443310-2d24a526-efe0-4c12-9a86-572453bcf70d.png)
![PZEM Wiring Diagram](https://user-images.githubusercontent.com/107752934/208443615-71dbae15-1b80-40bc-8f4d-3f62b595b41f.png)

# Installation
1. Install Node-js first (https://nodejs.dev/learn/how-to-install-nodejs)
2. Install Node-red (https://nodered.org/docs/getting-started/local)
3. Install MQTT Broker (https://mosquitto.org/)
4. Import code from this source code for node-red
5. Import arduino code into arduino
6. and change arduino code according your MQTT broker adress and change your Wi-Fi Settings on arduino

# Next Goal
- Adding wifi setting and login page
- Integrating device power with the power plug
- Reduce footprint of the smart plug size
