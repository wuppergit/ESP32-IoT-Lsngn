/*
 *  Funksteckdosen steuern mit Blynk
 */ 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <RCSwitch.h>                      // einbinden von rc-switch

#define BLYNK_PRINT Serial
#define TX_PIN 23                          // Sender Pin (GPIO23 - Pin D23)

RCSwitch mySwitch = RCSwitch();

const char* ssid = "Ihre_SSID";         // Wert anpasseen
const char* password = "IHR_Passwort";  // Wert anpassen
// Blynk-App auth-Token aus der Email
char auth []= "6z5tMeXoYIWptwHDLX9IYed9UeFjggvs";  

BLYNK_WRITE(V1) {                                   // Blynk Widget sendet die Daten
  int pinData = param.asInt(); 
  if (pinData == 1) {
    mySwitch.send(5260625, 24);  
  } else {
    mySwitch.send(5260628, 24);  
  } 
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  mySwitch.enableTransmit(TX_PIN);         // senden ermöglichen
}

void loop() {
  Blynk.run();
}

