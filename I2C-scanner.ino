/**
 * I2C Scanner
 */
 #include <Wire.h>

#define SDA_PIN     21
#define SCL_PIN     22

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("Start I2C Scanner");
}
 
void loop() {
  byte error, addresse;
  int anz = 0;
  for (addresse = 1; addresse < 127; addresse++ ) {
    Wire.beginTransmission(addresse);
    error = Wire.endTransmission(); 
    if (error == 0) {
      Serial.print("I2C-Gerät an Adreese 0x");
      if (addresse<16)
        Serial.print("0");
      Serial.print(addresse,HEX);
      Serial.println("  gefunden!");  
      anz++;
    } else if (error==4) {
      Serial.print("Unbekannter Fehler bei Adresse 0x");
      if (addresse<16)
        Serial.print("0");
      Serial.println(addresse,HEX);
    }    
  }
  if (anz == 0)
    Serial.println("Keine I2C Geräte gefunden");
  else
    Serial.println("Ende Scan"); 
  delay(10000);                 // nächster Scnavorgang nach 10 Sekunden
}
