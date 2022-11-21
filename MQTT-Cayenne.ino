/*
 * ESP32 mit Cayenne verbinden
 */
#define CAYENNE_PRINT Serial 
#include <CayenneMQTTESP32.h>                       // Header Cayenne



const char* ssid = "Ihre_SSID";             // Wert anpasseen
const char* password = "IHR_Passwort";      // Wert anpassen

// Cayenne authentication Angaben
char username[] = "8ef6b600-2--------------------------267";
char password[] = "5f72e-----------------------ecdd3a";
char clientID[] = "ce2f------------------------e7f75f9";


void setup() {
	Serial.begin(115200);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default Funktion für das periodische Senden von Daten an Cayenne
CAYENNE_OUT_DEFAULT() {	
	Cayenne.virtualWrite(0, millis()); // Sendet Zeitangabe in Millisekunden über den virtuellen Kanal 0.
}

// Default Funktion für das Empfangen von Daten von Cayenne
CAYENNE_IN_DEFAULT() {
    CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}

