#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"


const int buttonPin = 33;
const int ledPin = 22;
unsigned long czas_startu=0;
int ostatni_odczyt = HIGH;
int stan_przycisku = HIGH;

void setup() {
  
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
  int odczyt = digitalRead(buttonPin);
  if(odczyt != ostatni_odczyt){
    czas_startu=millis();
  }
  if(millis()-czas_startu>=50){
    if(stan_przycisku != odczyt)
    {
      stan_przycisku=odczyt;
      if(odczyt == LOW){
        digitalWrite(ledPin, HIGH);
        Serial.println("Button pressed");
      }
      else{
        digitalWrite(ledPin, LOW);
      }
    } 
  }
  ostatni_odczyt=odczyt;
}
