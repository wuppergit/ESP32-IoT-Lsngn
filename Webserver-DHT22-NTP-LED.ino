/*
 * messen der Temperatur und der Luftfeuchtigkeit mit dem DHT22
 * hinzufügen eines Zeitstemples und Ausgabe in einem Browser
 * LED über eine Browser-Eingabe steuern
 */
#include <WiFi.h>                           // für WiFi 
#include <WiFiUdp.h>
#include "DHTesp.h"                         // DHT22 Bibliothe fuer ESP32
#include <NTPClient.h>                      // für NTP

#define LED_PIN    2                        // GPIO2, PIN G2
#define DHT22_PIN 13                        // Pin für den DHT22-Sensor 
#define NTP_OFFSET 2 * 60 * 60              // In seconds
#define NTP_INTERVAL 60 * 1000              // In miliseconds
#define NTP_ADDRESS "3.de.pool.ntp.org"     // "ptbtime1.ptb.de" //   "europe.pool.ntp.org"

const char* ssid = "Ihre_SSID";             // Wert anpasseen
const char* password = "IHR_Passwort";      // Wert anpassen

WiFiServer serverWiFi (80);                 // Port für Webserver
DHTesp dht;                                 // Objekt bilden
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

float temperatur;
float luftFeuchte;
String zeitFormattedNTP;

// sendet eine Antwort an den WiFi-Client
void wifiSend (WiFiClient client) {  
  lesenDHT22();
  holenNTP();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html"); 
  client.println();
  // der Inhalt der HTTP-Antwort folgt auf den Header
  client.print ("ESP32 <br>"); 
  client.print ("Zeit:" + zeitFormattedNTP + "<br>");
  client.print ("Temperatur:" + String(temperatur) + "<br>");
  client.print ("Luftfeuchtigkeit: " + String(luftFeuchte) + "<br>");
  client.print ("Klick <a href=\"/H\">hier</a> um die LED an Pin 2 einzuschalten.<br>");
  client.print ("Klick <a href=\"/L\">hier</a> um die LED an Pin 2 auszuschalten.<br>");  
  // die HTTP-Antwort endet mit einer weiteren blank Zeile
  client.println(); 
}

// bearbeitet eine Anfrage von dem WiFi-Client
void wifiReceive (WiFiClient client) {
  Serial.println("Neue Anfrage.");          // Ausgabe einer Meldung im Seriellen Monitor
  String currentLine = "";                  // String-Variable f. eingehende Daten
  int cnt = 0;                              // Zähler while client.connected   
  while (client.connected()) {              // while-Shleife solange Client-Verbindung  
    cnt++;                                  // Schleifenzähler um 1 erhöhen    
    if (client.available()) {               // sind Bytes vom client zu lesen?               
      char c = client.read();               // lesen eines Bytes in Varaible c
      Serial.print(c);                      // Ausgabe des Bytes im Seriellen Monitor
      if (c == '\n') {                      // if the byte is a newline character
         // das Ende der HTTP-Anfrage ist eine blank-Zeile und zwei newline Zeichen hintereinander
         if (currentLine.length() == 0) {    // Ende der HTTP-Anforderung durch den Client        
          wifiSend(client);            
          break;                            // beenden der while client.connected Schleife
        } else {                            // liegt ein newline vor
          currentLine = "";                 // Variable currentLine löschen
        }
      } else if (c != '\r') {               // alles andere als ein Wagenrücklauf-Zeichen
        currentLine += c;                   // Zeichen der Variablen currentLine hinzufügen
      }
      // war die Client-Anfrage "GET /H" or "GET /L" ?
      if (currentLine.endsWith("GET /H")) {
        digitalWrite(LED_PIN, HIGH);        // GET /H schaltet die LED an
      }
      if (currentLine.endsWith("GET /L")) {
        digitalWrite(LED_PIN, LOW);         // GET /L schaltet die LED aus
      }
    }                                       // end if client.available
    if (cnt > 10000) {                      // erzwingt disconnect fehlendes client.available
      break;
    }     
  }                                         // end while client.connected      
  client.stop();                            // Verbndung schliessen
  Serial.println("Client Disconnected.");
  Serial.println();      
}


// lesen der DHT22 Messwerte 
void lesenDHT22() {
  temperatur = dht.getTemperature();
  luftFeuchte = dht.getHumidity();
  if (isnan(temperatur) || isnan(luftFeuchte)) {
    Serial.println("Fehler beim Lesen des DHT Sensors!");
  } else {
    Serial.print("Temperatur: ");
    Serial.print(temperatur);
    Serial.print(" °C  -  Luftfeuchtigkeit: ");
    Serial.print(luftFeuchte);
    Serial.println(" %");
  }  
}

// holen der aktuellen Zeit
void holenNTP() {
  timeClient.update();   // aktualisieren des Zeitstempels
  zeitFormattedNTP = timeClient.getFormattedTime();  // Ergebnis speichern
  // Serial.println(timeClient.getFormattedTime()); 
  Serial.println(zeitFormattedNTP); 
// unsigned long   zeitNTP = timeClient.getEpochTime();
//  Serial.println(zeitNTP); 
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);   
  Serial.print("Verbindungsaufbau zu ");    // Verbindungsaufbau zum WiFi-Netzwerk
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }  
  Serial.println("");                       // Verbindung aufgebaut
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();  
  Serial.println("Start WiFi Server!");  
  serverWiFi.begin();
  Serial.println("Start DHT22 sensor!");
  dht.setup(DHT22_PIN, DHTesp::DHT22);
  Serial.println("Start NTP Client!");
  timeClient.begin();
}

void loop() {
  WiFiClient client = serverWiFi.available();  // horcht auf Client-Anfragen
  if (client) {                             // fragt ein Client an?
    wifiReceive (client);                   // Anfrage aufbereiten
  }      
  delay(1);
}
