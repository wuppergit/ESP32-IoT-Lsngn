/*
 * externer Interrupt
 */
#define INTERR_PIN    4                       // externer Interrupt an GPIO4

volatile int interruptStatus, alteZeit = 0, debounceZeit = 100;
int interruptZaehlerGesamt;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// ISR-Routine 
void IRAM_ATTR isrHandler() {
  if  ( (millis() - alteZeit) > debounceZeit) {
    portENTER_CRITICAL_ISR(&timerMux);
    interruptStatus++;
    portEXIT_CRITICAL_ISR(&timerMux);  
    alteZeit = millis();                      // letzte Zeit merken
  }   
}
 
void setup() { 
  Serial.begin(115200); 
  pinMode(INTERR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERR_PIN), isrHandler, FALLING);
}
 
void loop() { 
  if (interruptStatus > 0) { 
    portENTER_CRITICAL(&timerMux);
    interruptStatus--;
    portEXIT_CRITICAL(&timerMux); 
    interruptZaehlerGesamt++; 
    Serial.print("Interrupt: Gesamtzahl Interrupts: ");
    Serial.println(interruptZaehlerGesamt); 
  }
}
