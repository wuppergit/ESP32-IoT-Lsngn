/**
 * empfangen von 433MHz-Signalen
 */
#include <RCSwitch.h>                      // einbinden von rc-switch

#define TX_PIN 23                          // Sender Pin (GPIO23 - Pin D23)

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200); 
  mySwitch.enableTransmit(TX_PIN);       // senden ermöglichen
}

void loop() {
  if (Serial.available() > 0) { 
     float codeSwitch = Serial.parseFloat(); 
     mySwitch.send(codeSwitch, 24);  
  }
  delay(1);  
}
