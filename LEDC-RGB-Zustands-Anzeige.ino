/*
 * ESP32 LEDC Software RGB- Zustandsanzeige
 */
#define LED_PVM_KANAL_R    0         // Kanal 0 für rot 
#define LED_PVM_KANAL_G    1         // Kanal 1 für grün 
#define LED_PVM_KANAL_B    2         // Kanal 2 für blau 
#define LED_AUFLOESUNG     13        // 13-bit-Auflösung 
#define LED_BASE_FREQ      5000      // 5000 Hz als LEDC Basis - Frequenz
#define LED_PIN_R          0
#define LED_PIN_G          4
#define LED_PIN_B          5   

// Simulation des Arduino-analogWrite
// Wert muss zwischen 0 und valueMax iiegen
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // Berechnugn des EIN-Zyklus (duty), 8191 ist =  2 ^ 13 (Auflösung) - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);          // Wert an LED ausgeben
}

// Aufruf der analogWrite-Routibe für jede RGB-Farbe
//void rgbAusgeben(uint32_t rot, uint32_t gruen, uint32_t blau) {
void rgbAusgeben(uint32_t rgbWerte[]) {  
  ledcAnalogWrite(LED_PVM_KANAL_R, rgbWerte[0]);
  ledcAnalogWrite(LED_PVM_KANAL_G, rgbWerte[1]);
  ledcAnalogWrite(LED_PVM_KANAL_B, rgbWerte[2]); 
}

// ermitteln der RGB-Kombination für den als Parameter übergebenen Zustand
void zustandAnzeigen (int zustand) {    
  uint32_t zustaende[6][3]  = {  0, 255, 0,  150, 200, 0,   255, 255,   0,
                               220, 150, 0,  255,   0, 0,   255,   0, 100};                                 
  rgbAusgeben(zustaende[zustand]);   //RGB-Werte übergeben
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

// die Schleife, die immer wieder durchlaufen wird
void loop() { 
  for (int i = 0; i < 6; i++) {
    zustandAnzeigen (i);
    delay(2000);
  }
}
