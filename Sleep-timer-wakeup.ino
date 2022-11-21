/*
 * Deep Sleep mit Timer Wakeup
*/
#define TIME_TO_SLEEP  5 * 1000000            // "Schlafzeit" in Microsekunden => 5 Sekunden

RTC_DATA_ATTR int bootCount = 0;              // Zähler in den RTC-Speicher legen

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

void callback(){                            // Platzhalter für weitere Befehle
}

void setup(){
  Serial.begin(115200);
  delay(1000);                              // etwas Zeit; wichtig - nicht löschen ! 
  ++bootCount;                              // wird bei jedem Boot-Vorgang um einen hochgezählt
  Serial.println("Boot-Nummer: " + String(bootCount));
  printWeckQuelle();                        // Weckquelle ausgeben
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
  Serial.println("Start Deep-Sleep-Modus");    
  esp_deep_sleep_start();                   // in den Deep-Sleep-Modus versetzen
  Serial.println("Diese Stelle sollte nie erreicht werden");
}

void loop(){                                // wird nie ausgeführt
}
