/*
 *  Blynk sendet ine email
 */ 
 
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/* Set this to a bigger number, to enable sending longer messages */
//#define BLYNK_MAX_SENDBYTES 128

const char* ssid = "Ihre_SSID";         // Wert anpasseen
const char* password = "IHR_Passwort";  // Wert anpassen
// Blynk-App auth-Token aus der Email
char auth []= "6z5tMeXoYIWptwHDLX9IYed9UeFjggvs";  

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  Blynk.email("brandes.udo@gmail.com", "Subject", "Test Blynk Projekt Email");
}

void loop() {
  Blynk.run();
}

