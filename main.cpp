#include <Arduino.h>

const int pinLED = 32;
const int pinRele = 19;
const int pinSensorPIR = 35;
const int pinBotao = 27;
bool aceso = false;

void setup() {
  Serial.begin(115200);

  pinMode(pinSensorPIR, INPUT_PULLUP);
  attachInterrupt(pinSensorPIR, falling_isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinBotao), falling_isr2, FALLING);

  pinMode(pinLED, OUTPUT);
  pinMode(pinRele, OUTPUT);
  pinMode(pinBotao, INPUT);
  digitalWrite(pinLED, LOW);
  digitalWrite(pinRele, LOW);
}

void loop() {
  Serial.println(digitalRead(pinSensorPIR));
  if(aceso)
  {
    digitalWrite(pinLED, HIGH);
    digitalWrite(pinRele, HIGH);
    delay(5000);
  }
  else if(!aceso || digitalRead(pinBotao))
  {
    digitalWrite(pinLED, LOW);
    digitalWrite(pinRele, LOW);
  }
}

void rising_isr(){
  aceso = true;
  attachInterrupt(pinSensorPIR, falling_isr, FALLING);
}

void falling_isr(){
  aceso = false;
  attachInterrupt(pinSensorPIR, rising_isr, RISING);
}

void falling_isr2(){
  aceso = false;
  digitalWrite(pinLED, LOW);
  digitalWrite(pinRele, LOW);
  attachInterrupt(pinSensorPIR, rising_isr, HIGH);
}
