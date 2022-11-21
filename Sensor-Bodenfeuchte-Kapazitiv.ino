/*
 * messen der Bodenfeuchte mit einem kapazitiven Sensor
 */ 
#define BODEN_SENSOR_A_PIN   33                // Pin für den Boden-Sensor analog

int schwellenWert = 40;                       // anzupassender Schwellenwert 

// lesen der Messwerte und Aktion ausführen (hier Serial Monitor)
void lesenMesswert() {
  int analogValue = analogRead(BODEN_SENSOR_A_PIN);
  int feuchtigkeit = map(analogValue, 0, 4095, 100, 0);//maps the analog value - 100% very wet/0% - very dry
  Serial.print("Feuchtigkeit: ");
  Serial.print(analogValue);
  Serial.print(" ");
  Serial.print(feuchtigkeit);
  Serial.print("%");

  if (feuchtigkeit >= schwellenWert) {
    Serial.println(" - Keine Bewässerung nötig");
  } else {
    Serial.println(" - Die Pflanzen brauchen Wasser");
  }
}

void setup() {
  Serial.begin(115200); 
}

void loop() {  
  lesenMesswert();
  delay(3000);
}
