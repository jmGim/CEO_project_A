#include <Arduino.h>
#include <Wire.h>

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

#define SIG_PIN         14
#define BUZZER_PIN      16

int Sound = 900;
int detected = 0;


void setup()
{
  Serial.begin(115200);

  pinMode(SIG_PIN, INPUT);

  Serial.println("Starting");
}


void loop()
{
  detected = digitalRead(SIG_PIN);
  Serial.println(detected ? "Detected!!!" : "---");

  // Detected Something -> Buzzer On
  if ( detected ) {
    Serial.println("!!! Danger !!!");
    tone(BUZZER_PIN , Sound);
    delay(300);
    noTone(BUZZER_PIN);
  }

  // Detected Nothing -> Buzzer OFF
  else {
    noTone(BUZZER_PIN );
    delay(100);
  }

  delay(200);
}
