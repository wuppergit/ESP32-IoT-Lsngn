/*
 * RDID RC522 Auswertung der UID / Zugangskontrolle
 */
#include <SPI.h>
#include <MFRC522.h>                // für RFID RC522

#define LED_PIN         2           // LED-Pin
#define RST_PIN         22          // RST-Pin
#define SDA_PIN         21          // SS- bzw. SDA-Pin

MFRC522 mfrc522(SDA_PIN, RST_PIN);  // MFRC522-Instanz erstellen

void setup() {
  Serial.begin(115200);   
  SPI.begin();                      // SPI-Bus initialisieren
  mfrc522.PCD_Init();               // RFID RC522 initialisieren
  Serial.println("Ein RFID-Tag an den Leser halten...");
  Serial.println();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}
void loop() {
  String rfidTag= "";
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() &&          // liegt eine neue Karte vor?
    mfrc522.PICC_ReadCardSerial() ) {           // ist die Auswahl einer Karte erfolgreich?
    Serial.print("RFID-Tag / Karten-ID :");
    for (byte i = 0; i < mfrc522.uid.size; i++)  {                //  Karten-ID behandeln
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  // Monitor-Ausgabe
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  // Ausgabe in String
      rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Aktion : ");
    rfidTag.toUpperCase();
    if (rfidTag.substring(1) == "99 70 13 2B")  {       // hier den zuzulassenden RFID-Tag angeben
      Serial.println("Zugang genehmigt \n");
      digitalWrite(LED_PIN, HIGH);
      delay(3000);
    } else {
      Serial.println("Zugang verweigert!\n");
      digitalWrite(LED_PIN, LOW);
      delay(3000);
    }
  }
} 
