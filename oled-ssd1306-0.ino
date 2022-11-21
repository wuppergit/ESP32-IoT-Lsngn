/**
 * I2C OLED-Display ssd 1306  Ausgabe Hallo ESP32
 */
#include "SSD1306.h"                                  // Header SSD1306

SSD1306  display(0x3c, 21, 22);                       // SSD1306 Instanz
int i = 0;

// zeichnen Grundfunktion
void zeichneHalloESP32() {
  i++;
  String hallo = "Hallo ESP32  " + String(i);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
//  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, hallo);
}

// generelle Zeichnen-Funktion
void zeichnen() {
  display.clear();                                    // Bildschirm löschen
  zeichneHalloESP32();
  display.display();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  display.init();
  display.flipScreenVertically();
//  display.setFont(ArialMT_Plain_10);
}

void loop() {  
  zeichnen();
  delay(2000);
}
