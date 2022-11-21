/*
 * Hall-Messung mit dem internen Sensor
 */

void setup() {
  Serial.begin(115200);
}
 
void loop() {
  int messWert = 0;
  messWert = hallRead();
  Serial.print("Hall sensor Messung: ");
  Serial.println(messWert); 
  delay(1000);
}
