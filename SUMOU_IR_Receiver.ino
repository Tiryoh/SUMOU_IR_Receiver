/*
 * SUMOU IR Receiver
 * Copyright 2016 Tiryoh
 * Licensed under the MIT license
 * http://tiryoh.mit-license.org
 */

/* 
 * ATmega328P Timer
 * Timer0 PWM5,PWM6,delay(),millis(),micros()
 * Timer1 PWM9,PWM10,ServoLib
 * Timer2 PWM3,PWM11,tone(),MsTimer2Lib 
 */

#include <IRremote.h>
#define RECV_PIN 11

//IR HEX
#define StartSwitch 0xA90
#define StopSwitch 0xA80

IRrecv irrecv(RECV_PIN);
decode_results results;

#define DEBUG
unsigned long timer = 0, conf = 0;
int input = 0;

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

bool start_recv(void) {
  if (irrecv.decode(&results)) {
    if (results.decode_type == SONY && results.value == StartSwitch) {
#ifdef DEBUG
      Serial.println("start");
#endif
      return true;
    }
    irrecv.resume();
    return false;
  }
}

bool stop_recv(void) {
  if (irrecv.decode(&results)) {
    if (results.decode_type == SONY && results.value == StopSwitch) {
#ifdef DEBUG
      Serial.println("stop");
#endif
      return true;
    }
    irrecv.resume();
    return false;
  }
}

void loop() {
#ifdef DEBUG
  Serial.println("PROGRAM START");
#endif

  while (!start_recv()) {
#ifdef DEBUG
    Serial.println("waiting for start signal");
#endif
    delay(10);
  }

  //WRITE START PROCESS HERE
#ifdef DEBUG
  Serial.println("wait 5sec");
#endif
  digitalWrite(2, HIGH);
  delay(5000);
  //END OF START PROCESS

  while (!stop_recv()) {
    //WRITE FIGHT PROCESS HERE
#ifdef DEBUG
    Serial.println("moving");
#endif
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
    delay(50);
    //END OF FIGHT PROCESS
  }

  while (1) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}

