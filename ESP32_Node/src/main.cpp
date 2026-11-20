#include <Arduino.h>

const int buttonPin = 33;
const int ledPin = 22;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("PRZYCISK WCISNIETY");
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}