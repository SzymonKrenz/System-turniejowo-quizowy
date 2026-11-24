#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"
#include <WebSocketsClient.h>


const char* TEAM_NAME = "Leliwa";
const int buttonPin = 33;
const int ledPin = 22;
unsigned long czas_startu=0;
int ostatni_odczyt = HIGH;
int stan_przycisku = HIGH;
WebSocketsClient webSocket;
void WebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket rozlaczony");
      digitalWrite(ledPin, LOW);
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket polaczony");
      webSocket.sendTXT(TEAM_NAME);
      break;
    case WStype_TEXT:{
      Serial.printf("WebSocket odebrano wiadomosc: %s\n", payload);
      String msg = (char*)payload;
      msg.trim();
      if (msg == "LED_ON") {
        Serial.println("Zapalanie diody LED");
        digitalWrite(ledPin, HIGH);
      } else if (msg == "LED_OFF") {
        digitalWrite(ledPin, LOW);
      }
      break;
    }
      default:
      break;
  }
}

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
  webSocket.begin(SERVER_IP, SERVER_PORT, "/ws");
  webSocket.onEvent(WebSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
  int odczyt = digitalRead(buttonPin);
  if(odczyt != ostatni_odczyt){
    czas_startu=millis();
  }
  if(millis()-czas_startu>=50){
    if(stan_przycisku != odczyt)
    {
      stan_przycisku=odczyt;
      if(odczyt == LOW){
        Serial.println("Przycisk wcisniety");
        webSocket.sendTXT("BUZZ");
      }
    } 
  }
  ostatni_odczyt=odczyt;
}
