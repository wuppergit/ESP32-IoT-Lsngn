/*
 * messen der Helligkeit mit einem Licht Sensor  / Dämmerungsschalter
 */ 
 #define LICHT_SENSOR_PIN   32                // Pin für den Licht-Sensor

int tag = 3500;                               // Schwellenwert Tag
int nacht = 900;                              // Schwellenwert Nacht
int messWert = 0;                             // Messwert

// lesen der Lichtmesswerte und Aktion ausführen (hier Serial Monitor)
void lesenHelligkeit() {
  messWert = analogRead(LICHT_SENSOR_PIN);
  if (messWert < nacht) {  
    Serial.print("Nachtfunktio - Messwert: ");    
    Serial.println(messWert);    
  } else if (messWert > tag) { 
    Serial.print("Tagfunktio - Messwert: ");    
    Serial.println(messWert);      
  } else {
    Serial.print("Normalbetrieb - Messwert: ");    
    Serial.println(messWert); 
  } 
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Start Helligeit messen: ");   
}

void loop() {  
  lesenHelligkeit();
  delay(2000);                        // Pause um 2.000 Milli-Sekunden
}
