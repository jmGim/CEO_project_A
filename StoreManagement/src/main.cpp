#include <Arduino.h>
#include <Wire.h>
#include "ESP8266_ISR_Servo.h"

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

#define SWITCH          14
#define BUZZER_PIN      16
#define TRIG_PIN        13
#define ECHO_PIN        12
#define DOOR_PIN        2

#define S_CLOSE         0
#define S_OPEN          1
#define D_CLOSE         0
#define D_OPEN          1

int door_open_degree = 45;
int door_close_degree = 135;

int Store_State = S_CLOSE;
int Door_State = D_CLOSE;

int Sound = 900;
long duration;
float distance;

int servoIndex  = -1;

void setup()
{
  Serial.begin(115200);

  pinMode(SWITCH, INPUT);
  // pinMode(TRIG_PIN, OUTPUT);
  // pinMode(ECHO_PIN, INPUT);
  servoIndex = ISR_Servo.setupServo(2, MIN_MICROS, MAX_MICROS);
  
  delay(200);
  Serial.println("Starting");

  Store_State = S_OPEN;
  Door_State = D_OPEN;

  if (servoIndex != -1)
    Serial.println(F("Setup Servo1 OK"));
  else
    Serial.println(F("Setup Servo1 failed"));
}

void loop()
{

  int position;

  if (servoIndex != -1){
    for (position = 0; position <= 180; position++){
      ISR_Servo.setPosition(servoIndex, position);
      delay(100);
    }
  }
  delay(1000);


  if (servoIndex != -1){
    for (position = 180; position >= 0; position--){
      ISR_Servo.setPosition(servoIndex, position);
      delay(100);
    }
  }
  delay(1000);
  
  // if ( Store_State == S_OPEN )
  // {
  //   Serial.println(digitalRead(SWITCH));
  //   if( digitalRead(SWITCH) == 0 )
  //   {
  //     Serial.println("Switch Clicked");
  //     if(Door_State == D_CLOSE){
  //       Serial.println("Door Open!");
  //       ISR_Servo.setPosition(DOOR_PIN, door_open_degree);
  //       Door_State = D_OPEN;
  //       delay(1000);
  //     }
  //     else if(Door_State == D_OPEN){
  //       Serial.println("Door Close!");
  //       ISR_Servo.setPosition(DOOR_PIN, door_close_degree);
  //       Door_State = D_CLOSE;
  //       delay(1000);
  //     }

  //     delay(500);
  //   }
  // }
  // else if ( Store_State == S_CLOSE )
  // {
  //   // ISR_Servo.setPosition(DOOR_PIN, D_CLOSE);

  //   // digitalWrite(TRIG_PIN, LOW);
  //   // delayMicroseconds(2);
  //   // digitalWrite(TRIG_PIN, HIGH);
  //   // delayMicroseconds(10);
  //   // digitalWrite(TRIG_PIN, LOW);

  //   // duration = pulseIn(ECHO_PIN, HIGH);
  //   // Serial.print("Duration: ");
  //   // Serial.println(duration);
  //   // distance = duration * 0.017; // duration / 29 / 2

  //   // Serial.print(distance);
  //   // Serial.println("cm");
  //   // delay(500);

  //   // if (distance <= 20)
  //   // {
  //   //   tone(BUZZER_PIN , Sound);
  //   //   ISR_Servo.setPosition(2, 180);
  //   //   delay(100);
  //   // }
  //   // else
  //   // {
  //   //   noTone(BUZZER_PIN );
  //   //   ISR_Servo.setPosition(2, 0);
  //   //   delay(100);
  //   // }
  // }

  delay(20);
}
