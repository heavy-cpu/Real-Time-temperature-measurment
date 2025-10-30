
# Temperature Monitoring IoT System (ESP8266 + Blynk)

This project monitors body and ambient temperature using DS18B20 and DHT11 sensors, and transmits the data to the Blynk IoT platform via ESP8266 (NodeMCU). It provides health insights by classifying the temperature into Normal, Low, or Fever levels.

## Features
- Real-time body temperature monitoring (DS18B20)
- Ambient temperature and humidity sensing (DHT11)
- Automatic health status classification (Normal / Fever / High Fever)
- Wireless IoT dashboard using Blynk
- Serial monitoring for debugging and calibration

## Components Required
- ESP8266 (NodeMCU)
- DS18B20 Digital Temperature Sensor
- DHT11 Temperature & Humidity Sensor
- 4.7kΩ resistor (pull-up for DS18B20)
- Jumper wires and breadboard

## Circuit Connections

| Sensor | Pin | ESP8266 Pin |
|--------|-----|-------------|
| DS18B20 | Data | D2 |
| DHT11 | Data | D5 |
| Both Sensors | VCC | 3.3V |
| Both Sensors | GND | GND |

*Note:* Use a 4.7kΩ resistor between the DS18B20 data pin and 3.3V.

## Blynk Configuration
- **Template ID:** TMPL3kh0PxJyc  
- **Template Name:** TEMPERATURE MONITORING  
- **Auth Token:** Replace in code with your Blynk token  
- **Virtual Pins:**
  - V2 → Body Temperature (°C)
  - V3 → Health Status
  - V4 → Ambient Temperature (°C)
  - V5 → Humidity (%)
  - V6 → Fever Level Indicator

## Code Overview
- Reads DS18B20 multiple times for accuracy (averaged)
- Adds an adjustable offset for calibration (`TEMP_OFFSET`)
- Displays temperature and humidity on Blynk
- Outputs health status and fever level as descriptive text

## Installation and Usage
1. Clone this repository:

   git clone https://github.com/<your-username>/Temperature-Monitoring-IoT-ESP8266.git
2. Open `Temperature_Monitoring.ino` in Arduino IDE.
3. Install the following libraries:
   - Blynk
   - OneWire
   - DallasTemperature
   - DHT sensor library
4. Enter your WiFi credentials and Blynk Auth Token.
5. Upload to ESP8266 and open Serial Monitor (115200 baud).
6. Open Blynk app to view real-time sensor data.

## Example Output

Body Temperature: 36.7 °C
Fever Level (V6): NORMAL
DHT11 Temp: 30.0 °C, Humidity: 52%

 Feel free to modify and share.


