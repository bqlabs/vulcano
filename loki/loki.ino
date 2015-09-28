/*
 Fading

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * LED attached from digital pin 9 to ground.

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe

 http://www.arduino.cc/en/Tutorial/Fading

 This example code is in the public domain.

 */


int speed3Pin = 3;
int direction3Pin = 2;
int speed1Pin = 5;
int direction1Pin = 4;
int speed2Pin = 6;
int direction2Pin = 7;
int laserPin = 8;
bool shot = false;
bool shooting_up = false;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {

  Serial.begin(19200);
  pinMode(laserPin, OUTPUT); 

}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    //Serial.println(inputString);
    if (inChar == 'r') {
      right();
    }
    if (inChar == 'l') {
      left();
    }
    if (inChar == 'f') {
      front();
    }
    if (inChar == 'b') {
      back();
    }
    if (inChar == 'c') {
      clockwise();
    }
    if (inChar == 'a') {
      counterclockwise();
    }
    if (inChar == 's') {
      stop_all();
    }
    if (inChar == 'g') {
      shot = true;
    }
    Serial.flush();
  }
  gunshot();
  Serial.println(analogRead(A0));
}

void gunshot() {
  unsigned long currentMillis = millis();
  if (shot) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      shooting_up = true;

    }
    shot = false;
  }
  if (shooting_up) {
    if (currentMillis - previousMillis <= 500) {
      digitalWrite(laserPin, 1); 
    }
    else{
      shooting_up = false;
      digitalWrite(laserPin, 0);
      }
  }
}

void front() {
  digitalWrite(direction1Pin, 0);
  analogWrite(speed1Pin, 255);
  digitalWrite(direction2Pin, 1);
  analogWrite(speed2Pin, 255);
  analogWrite(speed3Pin, 0);
}

void back() {
  digitalWrite(direction1Pin, 1);
  analogWrite(speed1Pin, 255);
  digitalWrite(direction2Pin, 0);
  analogWrite(speed2Pin, 255);
  analogWrite(speed3Pin, 0);
}

void stop_all() {
  analogWrite(speed1Pin, 0);
  analogWrite(speed2Pin, 0);
  analogWrite(speed3Pin, 0);
}


void left() {
  digitalWrite(direction1Pin, 1);
  analogWrite(speed1Pin, 125);
  digitalWrite(direction2Pin, 1);
  analogWrite(speed2Pin, 125);
  digitalWrite(direction3Pin, 0);
  analogWrite(speed3Pin, 255);
}

void right() {
  digitalWrite(direction1Pin, 0);
  analogWrite(speed1Pin, 125);
  digitalWrite(direction2Pin, 0);
  analogWrite(speed2Pin, 125);
  digitalWrite(direction3Pin, 1);
  analogWrite(speed3Pin, 255);
}

void clockwise() {
  digitalWrite(direction1Pin, 0);
  analogWrite(speed1Pin, 150);
  digitalWrite(direction2Pin, 0);
  analogWrite(speed2Pin, 150);
  digitalWrite(direction3Pin, 0);
  analogWrite(speed3Pin, 150);
}

void counterclockwise() {
  digitalWrite(direction1Pin, 1);
  analogWrite(speed1Pin, 150);
  digitalWrite(direction2Pin, 1);
  analogWrite(speed2Pin, 150);
  digitalWrite(direction3Pin, 1);
  analogWrite(speed3Pin, 150);
}
