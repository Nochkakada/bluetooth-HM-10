#include <Arduino.h>
#include <Dabble.h>
#include <EEPROM.h>
#define out_A 6
#define out_B 7
#define out_C 8
#define out_D 9
int Sp = 0;
const int rx = 11;
const int tx = 10;
const int eeprom_addr = 266;

void setup() {
  for (int i = 6; i <= 9; i++)
    pinMode(i, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  Dabble.begin(9600, rx, tx);
  Sp = EEPROM.read(eeprom_addr);
}
void motor(int A, int B, int C, int D) {
  digitalWrite(out_A, A);
  digitalWrite(out_B, B);
  digitalWrite(out_C, C);
  digitalWrite(out_D, D);
  analogWrite(3, Sp);
  analogWrite(5, Sp);
  Serial.println(Sp);
}
void loop() {
  Dabble.processInput();
  EEPROM.update(eeprom_addr, Sp);
  if (GamePad.isUpPressed())
  {
    Serial.println("Pressed UP");
    motor(0, 1, 0, 1);

  }
  else if (GamePad.isDownPressed())
  {
    Serial.println("Pressed DOWN");
    motor(1, 0, 1, 0);

  }
  else  if (GamePad.isLeftPressed())
  {
    Serial.println("Pressed LEFT");
    motor(1, 0, 0, 1);

  }
  else if (GamePad.isRightPressed())
  {
    Serial.println("Pressed RIGHT");
    motor(0, 1, 1, 0);

  } else {

    motor(0, 0, 0, 0);
  }

  if (GamePad.isCrossPressed()) {
    Serial.println("WN Speed");
    Sp   -= 10;
    if (Sp <= 0) {
      Sp = 0;
    }
  }
  if (GamePad.isTrianglePressed()) {
    Serial.println("UP Speed");
    Sp   += 10;
    if (Sp >= 255) {
      Sp = 255;
    }
  }
}