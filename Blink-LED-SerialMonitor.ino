/*
 * LED Blink mit Ausgabe auf dem Seriellen Monitor
 */
int LEDPin = 2;                       // ESP32 blue-LED
int warten = 600;

// Vorbereitungs- und Initialisierungsroutine  
void setup() {
  // digital pin 2 als Ausgabe initialisieren
  pinMode(LEDPin, OUTPUT);
  // notw. f. korrekte Darstellung durch  Arduino-Serielle-Monitor  
  Serial.begin (115200);           
  Serial.println ("Start");
}

// die Schleife, die immer wieder durchlaufen wird
void loop() {  
  digitalWrite(LEDPin, HIGH);        // schaltet die LED ein
  Serial.println ("LED ein");
  delay(warten);                     // etwas warten
  digitalWrite(LEDPin, LOW);         // schaltet die LED eiaus
  Serial.println ("LED aus");
  delay(warten);                     // etwas warten
}
