#include "Volume.h" // Include the Volume library

Volume vol;
int played = 0;
int thresholdDown = 550;
int thresholdUp = 600;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  vol.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
 int lol = analogRead(A0);
 if (lol < thresholdDown) {
  vol.tone(440, 255);
  vol.delay(100);
  vol.tone(440,0);
  played = 1;
 } else if (lol >= thresholdUp && played == 1) {
  played = 0;
 }
 Serial.println(lol);
}
