/*
 * externer Interrupt
 */
#define INTERR_PIN    4                       // externer Interrupt an GPIO4

volatile int interruptStatus;
int interruptZaehlerGesamt;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// ISR-Routine 
void IRAM_ATTR isrHandler() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptStatus++;
  portEXIT_CRITICAL_ISR(&timerMux);  
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
