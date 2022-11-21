/**
 * I2C OLED-Display ssd 1306  Ausgabe Text und Bild
 */
#include "SSD1306.h"                                  // Header SSD1306
#include "flocke.h"                                   // vorbereitete Bilder

SSD1306  display(0x3c, 21, 22);                       // SSD1306 Instanz

int i = 0;

// zeichnen Grundfunktion
void zeichneHalloESP32() {
  i++;
  String hallo = "Hallo ESP32  " + String(i);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Calligraffitti_Regular_16);
  display.drawString(0, 0, hallo);
}

// zeichnet Bilder
void zeichneBild() {
  display.drawXbm(0, 0, flocke_width, flocke_height, flocke_bits);
    //display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}   

// generelle Zeichnen-Funktion
void zeichnen() {
  display.clear();                                    // Bildschirm löschen
  zeichneHalloESP32();
  display.display();
  delay (1000);
    
  display.clear();                                   
  zeichneBild();
  display.display();
  delay (1000);    
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  display.init();
  display.flipScreenVertically();
}

void loop() {  
  zeichnen();
  delay(2000);
}
