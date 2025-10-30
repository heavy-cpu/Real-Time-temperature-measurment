#define BLYNK_TEMPLATE_ID "TMPL3kh0PxJyc"
#define BLYNK_TEMPLATE_NAME "TEMPERATURE MONITORING"
#define BLYNK_AUTH_TOKEN "3euxu3DRRLb-rqyrH6n0CpPaAIxo9sil"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

char ssid[] = "elias";
char pass[] = "123elias";

// DS18B20 Body Temperature
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define TEMP_OFFSET 1.7  // Adjust for calibration

// DHT11 (Ambient)
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensorData() {
  // --- DS18B20 Body Temperature ---
  float sumTemp = 0;
  const int readings = 5;
  for (int i = 0; i < readings; i++) {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    sumTemp += tempC;
    delay(200);
  }
  float bodyTemp = (sumTemp / readings) + TEMP_OFFSET;

  Serial.print("Body Temperature: ");
  Serial.print(bodyTemp);
  Serial.println(" °C");

  Blynk.virtualWrite(V2, bodyTemp);

  // --- Health Status ---
  String status;
  if (bodyTemp < 36.0) {
    status = "Low Temperature ❄";
  } 
  else if (bodyTemp >= 36.0 && bodyTemp <= 37.5) {
    status = "Normal 😊";
  } 
  else {
    status = "Fever 🔥";
  }
  Blynk.virtualWrite(V3, status);

  // --- Fever Level Output (V6) ---
  String feverLevel;
  if (bodyTemp <= 37.2) {
    feverLevel = "NORMAL";
  } else if (bodyTemp <= 38.0) {
    feverLevel = "LOW FEVER";
  } else if (bodyTemp <= 39.0) {
    feverLevel = "FEVER";
  } else {
    feverLevel = "HIGH FEVER";
  }

  Blynk.virtualWrite(V6, feverLevel);

  Serial.print("Fever Level (V6): ");
  Serial.println(feverLevel);

  // --- DHT11 Ambient Data ---
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("DHT11 Temp: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  Blynk.virtualWrite(V4, t);
  Blynk.virtualWrite(V5, h);
}

void setup() {
  Serial.begin(115200);
  sensors.begin();
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(3000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}