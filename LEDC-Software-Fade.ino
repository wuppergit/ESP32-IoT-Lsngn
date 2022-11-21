/*
 * ESP32 LEDC Software Fade
 *  Code angelehnt an original Arduino Fade Beispiel:
 *  https://www.arduino.cc/en/Tutorial/Fade
 */
#define LED_PVM_KANAL      0         // der erste von 16 Kanälen wird belegt 
#define LED_AUFLOESUNG     13        // 13-bit-Auflösung 
#define LED_BASE_FREQ      5000      // 5000 Hz als LEDC Basis - Frequenz
#define LED_PIN            2

int helligkeit = 0;                  // Helligkeit der LED 
int fadeWeite = 5;                   // Anzahl der Schritte pro Fade

// Simulation des Arduino-analogWrite
// Wert muss zwischen 0 und valueMax liegen
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // Berechnugn des EIN-Zyklus (duty), 8191 ist =  2 ^ 13 (Auflösung) - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);          // Wert an LED ausgeben
}

// Vorbereitungs- und Initialisierungsroutine  
void setup() {
  // Setup des PVM-Timers und anbindn des Timers an einen LED-Pin
  ledcSetup(LED_PVM_KANAL, LED_BASE_FREQ, LED_AUFLOESUNG);
  ledcAttachPin(LED_PIN, LED_PVM_KANAL);
}

void loop() {
  // Helligkeit an dem gewählten PVM-Kanal festlegen
  ledcAnalogWrite(LED_PVM_KANAL, helligkeit);
  // Helligkeit um die gewählte Schrittbreite ändern
  helligkeit = helligkeit + fadeWeite;
  // an den Endpunkten des Fade-Vorgangs die Richtung ändern
  if (helligkeit <= 0 || helligkeit >= 255) {
    fadeWeite = -fadeWeite;
  }
  delay(30);
}
