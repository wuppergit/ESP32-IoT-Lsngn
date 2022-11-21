/*
 * ESP32 LEDC Software RGB- Fade von dunkel nach weiss
 */
#define LED_PVM_KANAL_R    0         // Kanal 0 für rot 
#define LED_PVM_KANAL_G    1         // Kanal 1 für grün 
#define LED_PVM_KANAL_B    2         // Kanal 2 für blau 
#define LED_AUFLOESUNG     13        // 13-bit-Auflösung 
#define LED_BASE_FREQ      5000      // 5000 Hz als LEDC Basis - Frequenz
#define LED_PIN_R          0
#define LED_PIN_G          2
#define LED_PIN_B          4

int helligkeitR = 0;                 // Helligkeit der roten LED 
int helligkeitG = 0;                 // Helligkeit der grünen LED 
int helligkeitB = 0;                 // Helligkeit der blauen LED 
int fadeWeite = 5;                   // Anzahl der Schritte pro Fade

// Simulation des Arduino-analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // Berechnugn des EIN-Zyklus (duty), 8191 ist =  2 ^ 13 (Auflösung) - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);          // Wert an LED ausgeben
}

// Vorbereitungs- und Initialisierungsroutine  
void setup() {
  // Setup der PVM-Timer und anbinden der Timer an einen LED-Pin
  ledcSetup(LED_PVM_KANAL_R, LED_BASE_FREQ, LED_AUFLOESUNG);
  ledcAttachPin(LED_PIN_R, LED_PVM_KANAL_R);
  ledcSetup(LED_PVM_KANAL_G, LED_BASE_FREQ, LED_AUFLOESUNG);
  ledcAttachPin(LED_PIN_G, LED_PVM_KANAL_G);
  ledcSetup(LED_PVM_KANAL_B, LED_BASE_FREQ, LED_AUFLOESUNG);
  ledcAttachPin(LED_PIN_B, LED_PVM_KANAL_B);    
}

void loop() {
  // Helligkeit an dem gewählten PVM-Kanal festlegen
  ledcAnalogWrite(LED_PVM_KANAL_R, helligkeitR);
  ledcAnalogWrite(LED_PVM_KANAL_G, helligkeitG);
  ledcAnalogWrite(LED_PVM_KANAL_B, helligkeitB);    
  // Helligkeit um die gewählte Schrittbreite ändern
  helligkeitR = helligkeitR + fadeWeite;
  helligkeitG = helligkeitG + fadeWeite;
  helligkeitB = helligkeitB + fadeWeite;
  // an den Endpunkten des Fade-Vorgangs die Richtung ändern
  if (helligkeitR <= 0 || helligkeitR >= 255) {
    fadeWeite = -fadeWeite;
  }
  if (helligkeitG <= 0 || helligkeitG >= 255) {
    fadeWeite = -fadeWeite;
  }
  if (helligkeitB <= 0 || helligkeitB >= 255) {
    fadeWeite = -fadeWeite;
  }
  delay(30);
}
