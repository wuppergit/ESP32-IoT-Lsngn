/*
 *  Blynk sendet eine email ( DHT22-Daten)
 */ 
 
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h" 

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/* Set this to a bigger number, to enable sending longer messages */
//#define BLYNK_MAX_SENDBYTES 128    für längere Emails
#define LED_PIN     2                       // GPIO2, PIN G2
#define DHT22_PIN   13                      // Pin für den DHT22-Sensor 

const char* ssid = "Ihre_SSID";         // Wert anpasseen
const char* password = "IHR_Passwort";  // Wert anpassen
// Blynk-App auth-Token aus der Email
char auth []= "6z5tMeXoYIWptwHDLX9IYed9UeFjggvs";  

DHTesp dht;                               
BlynkTimer timer;  

volatile float h = 0;
volatile float t = 0;

//  sendet die Sensordaten
void sendSensor() {
  h = dht.getHumidity();
  t = dht.getTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);    
  Blynk.begin(auth, ssid, password);
  dht.setup(DHT22_PIN, DHTesp::DHT22);   
  timer.setInterval(1000L, sendSensor);                      // Timer Intervall in mS 
}

void loop() {
  Blynk.run();
  timer.run();   
  if (t > 25) {                                             // bei überschreiten der max. Temperatur
    digitalWrite(LED_PIN, HIGH);
    Blynk.email("esp32.user@gmail.com", "Subject", "Test Blynk Projekt Email");
    delay (2000);                                           // warten bis heruntergekühlt
    digitalWrite(LED_PIN, LOW);
  }
}

