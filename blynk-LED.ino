/*
 *  LED steuern mit Blynk
 */ 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

const char* ssid = "Ihre_SSID";         // Wert anpasseen
const char* password = "IHR_Passwort";  // Wert anpassen
// Blynk-App auth-Token aus der Email
char auth []= "6z5tMeXoYIWptwHDLX9IYed9UeFjggvs";  

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
}
