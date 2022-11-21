/*
 * messen der Temperatur und der Luftfeuchtigkeit mit dem DHT22
 */ 
#include "DHTesp.h"                         // DHT22 Bibliothe fuer ESP32

#define DHT22_PIN 13                        // Pin für den DHT22-Sensor 

DHTesp dht;                                 // Instanz bilden

// lesen der DHT22 Messwerte und Aktion ausführen (hier Serial Monitor)
void lesenDHT22() {
  float temperatur = dht.getTemperature();
  float luftFeuchte = dht.getHumidity();
  if (isnan(temperatur) || isnan(luftFeuchte)) {
    Serial.println("Fehler beim Lesen des DHT Sensors!");
  } else {
    Serial.print("Temperatur: ");
    Serial.print(temperatur);
    Serial.print(" °C  -  Luftfeuchtigkeit: ");
    Serial.print(luftFeuchte);
    Serial.println(" %");
  }  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start DHT22 sensor!");
  dht.setup(DHT22_PIN, DHTesp::DHT22);       // AUTO_DETECT
}

void loop() {
  lesenDHT22();
  delay(2000);
}
