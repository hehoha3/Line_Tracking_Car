#include <Arduino.h>

//! Khai báo các Pin của L298N
#define motorEnableLeft 5
#define motorEnableRight 6
#define motorLeft_01 3
#define motorLeft_02 2
#define motorRight_01 4
#define motorRight_02 7

//! Khai báo các Pin của tcrt5000
#define ir_1 A6
#define ir_2 A5
#define ir_3 A4
#define ir_4 A3
#define ir_5 A2

const int leftMotorSpeed = 205;
const int rightMotorSpeed = 205;

int s1, s2, s3, s4, s5;

void readSensor() {
  s1 = digitalRead(ir_1);
  s2 = digitalRead(ir_2);
  s3 = digitalRead(ir_3);
  s4 = digitalRead(ir_4);
  s5 = digitalRead(ir_5);
}

void stopCar() {
  digitalWrite(motorLeft_01, LOW);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, LOW);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, 0);
}

void goForwardFull() {
  digitalWrite(motorLeft_01, HIGH);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, HIGH);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, rightMotorSpeed);
}

void goLeft_Lightly() {
  digitalWrite(motorLeft_01, LOW);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, HIGH);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed - 60);
  analogWrite(motorEnableRight, rightMotorSpeed);
}

void goLeft_Full() {
  digitalWrite(motorLeft_01, LOW);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, HIGH);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, 0);
  analogWrite(motorEnableRight, rightMotorSpeed);
}

void goRight_Lightly() {
  digitalWrite(motorLeft_01, HIGH);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, LOW);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, rightMotorSpeed - 60);
}

void goRight_Full() {
  digitalWrite(motorLeft_01, HIGH);
  digitalWrite(motorLeft_02, LOW);
  digitalWrite(motorRight_01, LOW);
  digitalWrite(motorRight_02, LOW);
  analogWrite(motorEnableLeft, leftMotorSpeed);
  analogWrite(motorEnableRight, 0);
}

void setup() {
  // báo các Pin là OUTPUT
  pinMode(motorEnableLeft, OUTPUT);
  pinMode(motorEnableRight, OUTPUT);
  pinMode(motorLeft_02, OUTPUT);
  pinMode(motorLeft_01, OUTPUT);
  pinMode(motorRight_01, OUTPUT);
  pinMode(motorRight_02, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readSensor();

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
    goForwardFull();
  } else if (((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) || ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))) {
    goLeft_Lightly();
  } else if (((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) || ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) || ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))) {
    goLeft_Full();
  } else if (((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1)) || ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))) {
    goRight_Lightly();
  } else if (((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0)) || ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0)) || ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))) {
    goRight_Full();
  } else {
    stopCar();
  }
}