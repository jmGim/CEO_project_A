#include <Arduino.h>
#include <Wire.h>
#include "ESP8266_ISR_Servo.h"

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

#define SW_DOOR         14
#define SW_STORE        15
// #define BUZZER_PIN      16
#define TRIG_PIN        13
#define ECHO_PIN        12
#define DOOR_PIN        2
#define SIG_PIN         16

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

  pinMode(SW_DOOR, INPUT);
  pinMode(SW_STORE, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SIG_PIN, OUTPUT);
  servoIndex = ISR_Servo.setupServo(DOOR_PIN, MIN_MICROS, MAX_MICROS);
  
  delay(200);
  Serial.println("Starting");

  Store_State = S_OPEN;
  Door_State = D_OPEN;

  if (servoIndex != -1)
    Serial.println(F("Setup Servo1 OK"));
  else
    Serial.println(F("Setup Servo1 failed"));

  digitalWrite(SIG_PIN, LOW);
}

void loop()
{

  // int position;
  // 
  // if (servoIndex != -1){
  //   for (position = 0; position <= 180; position++){
  //     ISR_Servo.setPosition(servoIndex, position);
  //     delay(100);
  //   }
  // }
  // delay(1000);


  // if (servoIndex != -1){
  //   for (position = 180; position >= 0; position--){
  //     ISR_Servo.setPosition(servoIndex, position);
  //     delay(100);
  //   }
  // }
  // delay(1000);
  
  Serial.print("----- State -----\nDoor : ");
  Serial.print(Door_State ? "OPEN" : "CLOSE");
  Serial.print(", Store : ");
  Serial.println(Store_State ? "OPEN" : "CLOSE");


  // Store OPEN -> Working Mode
  if ( Store_State == S_OPEN ) {
    if( digitalRead(SW_DOOR) == 1  ){
      // Door CLOSE -> OPEN
      if(Door_State == D_CLOSE) {
        Serial.println("Door Open!");
        ISR_Servo.setPosition(servoIndex, door_open_degree);
        Door_State = D_OPEN;
        delay(1000);
      }
      // Door OPEN -> CLOSE
      else if(Door_State == D_OPEN) {
        Serial.println("Door Close!");
        ISR_Servo.setPosition(servoIndex, door_close_degree);
        Door_State = D_CLOSE;
        delay(1000);
      }
    }

    // Stop Work Mode -> Change to Monitor Mode
    // Store -> CLOSE
    if( digitalRead(SW_STORE) == 1) {
      Store_State = S_CLOSE;
      Door_State = D_CLOSE;
      ISR_Servo.setPosition(servoIndex, door_close_degree);
    }
  }

  // Store CLOSE -> Monitor Mode
  else if ( Store_State == S_CLOSE ) {

    // Ultrasonic - Generate Trigger
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Calc Distance
    duration = pulseIn(ECHO_PIN, HIGH);
    Serial.print("Duration: ");
    Serial.println(duration);
    distance = duration * 0.017;  // distance = duration / 29 / 2

    // Print Distance (cm)
    Serial.print(distance);
    Serial.println("cm");

    // Monitor
    if (distance <= 20) {
      Serial.println("!!! Danger !!!");
      digitalWrite(SIG_PIN, HIGH);
      // tone(BUZZER_PIN , Sound);
      delay(300);
      // noTone(BUZZER_PIN);
    }
    else{
      digitalWrite(SIG_PIN, LOW);
      // noTone(BUZZER_PIN );
      delay(100);
    }
    
    // Stop Monitor Mode -> Change to Work Mode
    // Store -> OPEN
    if( digitalRead(SW_STORE) == 1) {
      digitalWrite(SIG_PIN, LOW);
      Store_State = S_OPEN;
      // noTone(BUZZER_PIN );
    }
  }

  delay(200);
}
