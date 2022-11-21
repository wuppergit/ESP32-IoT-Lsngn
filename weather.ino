/*
 * aktuelle Wetterdaten von OpenWeatherMap abrufen
 */

#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "Ihre_SSID";             // Wert anpasseen
const char* password = "IHR_Passwort";      // Wert anpassen
String stadtLand = "Berlin,de";             // Ort Stadt und Länderkennung

const String url = "http://api.openweathermap.org/data/2.5/weather?q=";
const String key = "f…………………………………………6";    // der API-Key
void setup() { 
  Serial.begin(115200); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Verbindung aufgebaut
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() { 
  if ((WiFi.status() == WL_CONNECTED)) {     // besteht Verbindung noch?
    HTTPClient http;
    http.begin(url + stadtLand + "&units=metric&APPID=" + key); // URL bestimmen    
    int httpCode = http.GET();               // Request absetzen
    if (httpCode > 0) {                      // returning code ok? (id.R. 200)
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Fehler beim HTTP request");
    }  
    http.end();                              // Ressourcen frei geben
  }
  delay(60000);                              // 60 sekunden warten 
}
