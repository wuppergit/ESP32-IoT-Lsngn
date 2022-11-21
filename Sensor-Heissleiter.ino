/*
 * messen der Temperatur mit einem Heissliter
 */ 
 #define TEMP_SENSOR_PIN   32                  // Pin für den Heissleiter-Sensor

int schwellWert = 1900;                        // Schwellenwert 
int messWert = 0;                              // Messwert

// lesen der Lichtmesswerte und Aktion ausführen (hier Serial Monitor)
void lesenTemperatur() {
  messWert = analogRead(TEMP_SENSOR_PIN);
  if (messWert < schwellWert) {  
    Serial.print("unter Schwellenwert - Messwert: ");    
    Serial.println(messWert);         
  } else {
    Serial.print("über Schwellenwert - Messwert: ");    
    Serial.println(messWert); 
  } 
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Start Temperatur messen: ");   
}

void loop() {  
  lesenTemperatur();
  delay(2000);                        // Pause um 1.000 Milli-Sekunden
}
