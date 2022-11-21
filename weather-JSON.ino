/*
 * aktuelle Wetterdaten von OpenWeatherMap abrufen
 */
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>                      // JSON aufbereiten
#include <TimeLib.h>                          // Zeit aufbereiten
 
const char* ssid = "Ihre_SSID";             // Wert anpasseen
const char* password = "IHR_Passwort";      // Wert anpassen
String stadtLand = "Berlin,de";             // Ort Stadt und Länderkennung

const String url = "http://api.openweathermap.org/data/2.5/weather?q=";
const String key = "f…………………………………………6";    // der API-Key

// holen der Wetterdaten über das Netz
int holenWetterDaten () {
  float temperatur;
  int sunset;
  if ((WiFi.status() == WL_CONNECTED)) {     // besteht Verbindung noch?
    HTTPClient http;
    http.begin(url + stadtLand + "&units=metric&APPID=" + key);     
    int httpCode = http.GET();               // Request absetzen
    if (httpCode > 0) {                      // returning code ok? (id.R. 200)
      String payload = http.getString();  
      Serial.println  (payload);
      StaticJsonDocument<1000> jsonDocument;     // Speicher für JSON bereit stellen
      auto err = deserializeJson(jsonDocument, payload); // JSON aufbereiten
      if (err) {         
        Serial.print  ("Fehler JSON-deserialize  ");
        Serial.println(err.c_str());
        sunset = 0;
      } else {     
        temperatur = jsonDocument ["main"] ["temp"];
        Serial.print("Temperatur  :  ");  
        Serial.print(temperatur);
        sunset = jsonDocument ["sys"] ["sunset"];
        Serial.print("    Sonnenuntergang um ");  
        Serial.print(hour(sunset));
        Serial.print(":");  
        Serial.print(minute(sunset));
        Serial.print(" Uhr");  
      }
    } else {
      Serial.println("Fehler beim HTTP request");
      sunset = 0;
    }  
    http.end();                              // Ressourcen frei geben
  }  
  return sunset;
}
 
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
  int sunset = holenWetterDaten();            // holen der Wetterdaten über das Netz
  delay(60000);                               // 60 sekunden warten 
}
