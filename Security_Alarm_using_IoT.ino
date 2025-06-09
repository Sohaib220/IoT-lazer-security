#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

const int ldrPin = A0;           // LDR analog pin
const int buzzerPin = 2;         // Buzzer pin
const int ledPin2 = 12;          // LED pin
const int ledPin = 13;           // LED pin
const int laserPin = 3;          // Laser pin
const int buttonPin = 4;         // Button pin
const int laserThreshold = 100;  // Threshold value for detecting laser interruption
const String phoneNumber = "+9647721425721";  // Phone number to call

SoftwareSerial SIM808(8, 7);     // RX, TX for SIM808



LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(laserPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.begin(9600);
  SIM808.begin(9600);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);`
  lcd.print("Security Alarm");
  lcd.setCursor(0, 1);
  lcd.print("System");
  
  delay(2000);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  if (digitalRead(laserPin) == LOW || ldrValue < laserThreshold) {
    // Laser interrupted or LDR detects low light
    digitalWrite(buzzerPin, HIGH);
    
    makeCall();
    
    while (digitalRead(buttonPin) == LOW) {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin,LOW);
      digitalWrite(ledPin2, HIGH);
      delay(1000);
      digitalWrite(ledPin2,LOW);
    }
    
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
  }
}

void makeCall() {
  Serial.println("Calling...");
  SIM808.println("ATD" + phoneNumber + ";");
  delay(100);  
  
  while (SIM808.available()) {
    Serial.write(SIM808.read());
  }
}
// this project is made by Sohaib Raid Rasheed
