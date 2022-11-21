/*
 * messen der Bodenfeuchte mit YL-69
 */ 
#define BODEN_SENSOR_A_PIN   33                // Pin für den Boden-Sensor analog
#define BODEN_SENSOR_D_PIN   17                // Pin für den Boden-Sensor digital
#define BODEN_SENSOR_VCC_PIN 34                // Pin für VCC Boden-Sensor

int schwellenWert = 50;                        // anzupassender Schwellenwert 

// lesen der YL-69 Messwerte und Aktion ausführen (hier Serial Monitor)
void lesenYL69() {
  digitalWrite(BODEN_SENSOR_VCC_PIN, HIGH); 
  delay (500);  
  int analogValue = analogRead(BODEN_SENSOR_A_PIN);
  int digitalValue = digitalRead(BODEN_SENSOR_D_PIN);
  int feuchtigkeit = map(analogValue, 0, 4095, 100, 0);//maps the analog value - 100% very wet/0% - very dry
  digitalWrite(BODEN_SENSOR_VCC_PIN, HIGH); 
  Serial.print("Feuchtigkeit: ");
  Serial.print(analogValue);
  Serial.print(" ");
  Serial.print(digitalValue);
  Serial.print(" ");
  Serial.print(feuchtigkeit);
  Serial.print("%");

  if (feuchtigkeit >= schwellenWert) {
    Serial.print(" - Keine Bewässerung nötig");
  } else {
    Serial.print(" - Die Pflanzen brauchen Wasser");
  }
  if (digitalValue == 1) {
    Serial.println(" - Alarm !Bewässerung dringend erforderlich");
  } else {
    Serial.println(" - alles in Ordnung ");
  }
  digitalWrite(BODEN_SENSOR_VCC_PIN, LOW); 
}

void setup() {
  pinMode(BODEN_SENSOR_VCC_PIN, OUTPUT);
  pinMode(BODEN_SENSOR_D_PIN, INPUT);
  digitalWrite(BODEN_SENSOR_D_PIN, LOW); 
  Serial.begin(115200); 
}

void loop() {  
  lesenYL69();
  delay(3000);
}
