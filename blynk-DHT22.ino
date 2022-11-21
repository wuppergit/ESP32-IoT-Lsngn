/*
 *  DHT22 sendet Daten an Blynk
 */ 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"         

#define BLYNK_PRINT Serial
#define DHT22_PIN 13         

const char* ssid = "Ihre_SSID";         // Wert anpasseen
const char* password = "IHR_Passwort";  // Wert anpassen
// Blynk-App auth-Token aus der Email
char auth []= "6z5tMeXoYIWptwHDLX9IYed9UeFjggvs";  

DHTesp dht;                               
BlynkTimer timer;                  

//  sendet die Sensordaten
void sendSensor() {
  float h = dht.getHumidity();
  float t = dht.getTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperatur ");
  Serial.print(t);
  Serial.print("   Luftfeuchtigkeit ");
  Serial.println(h);
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  dht.setup(DHT22_PIN, DHTesp::DHT22);  
  timer.setInterval(1000L, sendSensor);                    // Timer Intervall in mS 
}

void loop() {
  Blynk.run();
  timer.run();                                             // Timer aufrufen
}

