/*
 * Deep Sleep mit Touch Wakeup
*/
#define TOUCH_PIN0        T0                  // Touch 0 an GPIO4
#define TOUCH_PIN3        T3                  // Touch 3 an GPIO15

RTC_DATA_ATTR int bootCount = 0;              // Zähler in den RTC-Speicher legen
int schwellenWert = 40;                       // Schwellenwert zwischen berührtem / unberührtem Zustand größerer Wert => höhere Empfindlichkeit

// Ausgabe der Weckquelle
void printWeckQuelle(){
  esp_sleep_wakeup_cause_t weckQuelle = esp_sleep_get_wakeup_cause();
  switch(weckQuelle)   {
    case ESP_SLEEP_WAKEUP_EXT0 : 
      Serial.println("Weckquelle ist ein externes RTC_IO Signal"); 
      break;
    case ESP_SLEEP_WAKEUP_EXT1 : 
      Serial.println("Weckquelle ist ein externes RTC_CNTL Signal"); 
      break;
    case ESP_SLEEP_WAKEUP_TIMER : 
      Serial.println("Weckquelle ist ein Timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD :
      Serial.println("Weckquelle ist ein Touch Sensor"); 
      break;
    case ESP_SLEEP_WAKEUP_ULP : 
      Serial.println("Weckquelle ist ein ULP program"); 
      break;
    default : 
      Serial.printf("Weckquelle undefiniert: %d\n", weckQuelle); 
      break;
  }
}

// ausgeben des Touch Sensors
void printWeckQuelleTouchSensor(){
  touch_pad_t touchPinWakeUp = esp_sleep_get_touchpad_wakeup_status();
  switch(touchPinWakeUp)
  {
    case 0  : Serial.println("Auslöser Touch Sensor 0 an GPIO 4"); break;
    case 3  : Serial.println("Auslöser Touch Sensor 3 an GPIO 15"); break;
    default : Serial.println("auslösender Touch Sensor unbekannt"); break;
  }
}

void callback(){                            // Platzhalter für weitere Befehle
}

void setup(){
  Serial.begin(115200);
  delay(1000);                              // etwas Zeit; wichtig - nicht löschen ! 
  ++bootCount;                              // wird bei jedem Boot-Vorgang um einen hochgezählt
  Serial.println("Boot-Nummer: " + String(bootCount));

  printWeckQuelle();                        // Weckquelle ausgeben
  printWeckQuelleTouchSensor();             // Weckquelle Touch Sensor ausgeben
  touchAttachInterrupt(T0, callback, schwellenWert);  // T0 als Sensor bekannt machen
  touchAttachInterrupt(T3, callback, schwellenWert);  // T1 als Sensor bekannt machen
  esp_sleep_enable_touchpad_wakeup();       // Touch-Sensoren als Weckquelle fest legen  
  Serial.println("Start Deep-Sleep-Modus");    
  esp_deep_sleep_start();                   // in den Deep-Sleep-Modus versetzen
  Serial.println("Diese Stelle sollte nie erreicht werden");
}

void loop(){                                // wird nie ausgeführt
}
