/*
 *  PIR-Bewegungsmelder
 */ 
 #define PIR_SENSOR_PIN     13                // Pin für den PIR

int statusPIR = 0;                            // PIR-Staus

// lesen des PIR-Staus und Aktion ausführen (hier Serial Monitor)
void lesenPIR() {
  statusPIR = digitalRead(PIR_SENSOR_PIN);
  if (statusPIR == 0) {  
    Serial.println("keine Bewegung ");              
  } else {
    Serial.println("Bewegung erkannt");
  } 
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(PIR_SENSOR_PIN, INPUT); 
}

void loop() {  
  lesenPIR();
  delay(1000);                        // Pause um 1.000 Milli-Sekunden
}
