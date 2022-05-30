#include <Arduino.h>

#define speakerPin 14

const int trigPin = 13;
const int echoPin = 12;

int Sound = 900;
long duration;
float distance;

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(200);
  Serial.println("Starting");
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);
  distance = duration * 0.017; // duration / 29 / 2

  Serial.print(distance);
  Serial.println("cm");
  delay(500);

  if (distance <= 20)
  {
    tone(speakerPin, Sound);
  }

  else
  {
    noTone(speakerPin);
  }
  delay(20);
}