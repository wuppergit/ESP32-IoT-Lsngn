/**
 * senden und empfangen von 433MHz-Signalen
 */
#include "RCSwitch.h"                     // einbinden von rc-switch

#define TX_PIN   23                       // Sender Pin  (GPIO23 - Pin D23)
#define RX_PIN   22                       // Empfänger Pin (GPIO22 - Pin D22)

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200); 
  mySwitch.enableTransmit(TX_PIN);        // senden ermöglichen
  mySwitch.enableReceive(RX_PIN);         // empfangen ermöglichen
}

void loop() {
  if (Serial.available() > 0) { 
    float codeSwitch = Serial.parseFloat();
    mySwitch.send(codeSwitch, 24);  
  }
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    if (value == 0) {
      Serial.print("unbekanntes Protokoll");
    } else {
      Serial.print("empfangener Code: ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print("   Bitlänge: ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("   Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }
    mySwitch.resetAvailable();
  }
}
