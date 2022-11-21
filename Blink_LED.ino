/*
 * LED, die mitttels Touchsensoren ein- / ausgeschaltet werden
 * mit Ausgabe auf dem Seriellen Monitor
 */
int ledPin = 2;                       // GPIO2, PIN G2
int touchPinEin = 4;                  // T0, GPIO4, PIN G4 
int touchPinAus = T3;                 // T3, GPIO15, PIN G15 
int warten = 600;
int touchEin = 0;                     // eingelesener Wert für ein
int touchAus = 0;                     // eingelesener Wert für aus
// Vorbereitungs- und Initialisierungsroutine  
void setup() {
  // digital pin 2 als Ausgabe initialisieren
  pinMode(ledPin, OUTPUT);
  // notw. f. korrekte Darstellung durch  Arduino-Serielle-Monitor  
  Serial.begin (115200);
  Serial.println ("Start");
}
// die Schleife, die immer wieder durchlaufen wird
void loop() { 
 touchEin = touchRead(touchPinEin);  // lesen Touch ein
 touchAus = touchRead(touchPinAus);  // lesen Touch aus
 if (touchEin < 50) {
  digitalWrite(ledPin, HIGH);       // schaltet die LED ein
  Serial.println ("LED ein");
 }
 if (touchAus < 50) {
  digitalWrite(ledPin, LOW);        // schaltet die LED aus
  Serial.println ("LED aus");
 }
 delay(warten);                      // etwas warten
}