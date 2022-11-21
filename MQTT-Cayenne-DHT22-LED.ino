/*
 * ESP32 Cayenne gibt DHT22-Daten aus und steuert eine LED
 */
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>               // Header Cayenne
#include "DHTesp.h"                         // DHT22 Bibliothe fuer ESP32

#define LED_PIN    2                        // GPIO2, PIN G2
#define DHT22_PIN 13                        // Pin für den DHT22-Sensor 

const char* ssid = "Ihre_SSID";             // Wert anpasseen
const char* password = "IHR_Passwort";      // Wert anpassen

// Cayenne authentication Angaben
char username[] = "8ef6b600-2--------------------------267";
char password[] = "5f72e-----------------------ecdd3a";
char clientID[] = "ce2f------------------------e7f75f9";

DHTesp dht;                                 // Objekt bilden
float temperatur;
float luftFeuchte;
int ledStatus = 0;


// lesen der DHT22 Messwerte 
void lesenDHT22() {
  temperatur = dht.getTemperature();
  luftFeuchte = dht.getHumidity();
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

CAYENNE_OUT_DEFAULT() {
  lesenDHT22(); 
	Cayenne.celsiusWrite(0, temperatur);
  Cayenne.virtualWrite(1, luftFeuchte,TYPE_RELATIVE_HUMIDITY,UNIT_PERCENT);
  Cayenne.digitalSensorWrite(2,ledStatus);
}

CAYENNE_IN_DEFAULT() {
  if (request.channel == 3) {
    ledStatus = getValue.asInt();
    digitalWrite(LED_PIN,ledStatus);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_PIN, LOW);  
  Serial.println("Start DHT22 sensor!");
  dht.setup(DHT22_PIN, DHTesp::DHT22);    
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}


