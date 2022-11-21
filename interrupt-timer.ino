/*
 * Timer Interrupt
 */
#define LED_PIN    2                       // LED an GPIO2

volatile int ledStatus = 0;
volatile int interruptStatus;
int interruptZaehlerGesamt;
 
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptStatus++;
  portEXIT_CRITICAL_ISR(&timerMux);  
  if (ledStatus == 0) {
    ledStatus = 1;
    digitalWrite(LED_PIN, HIGH);
  } else {
    ledStatus = 0;
    digitalWrite(LED_PIN, LOW);
  }
}
 
void setup() { 
  Serial.begin(115200); 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 2000000, true);  // 2 Sekunden
  timerAlarmEnable(timer);
  pinMode(LED_PIN, OUTPUT); 
}
 
void loop() { 
  if (interruptStatus > 0) { 
    portENTER_CRITICAL(&timerMux);
    interruptStatus--;
    portEXIT_CRITICAL(&timerMux); 
    interruptZaehlerGesamt++; 
    Serial.print("Timer-Interrupt: Gesamtzahl Interrupts: ");
    Serial.println(interruptZaehlerGesamt); 
  }
}
