#include "Volume.h" // Include the Volume library

Volume vol;
int played = 0;
int thresholdDown;
int thresholdUp;

int generateMedium() {
  int res = 0;
  for (int i = 0; i < 20; i++) {
    int curr = analogRead(A0);
    res += curr/20;
  }
  return res;
}

void setup() {
  // put your setup code here, to run once:
  thresholdUp = generateMedium();
  thresholdDown = thresholdUp-50;
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  vol.begin();
}

int getMin(int lol) {
  int prev;
  do {
    prev = lol;
    lol = analogRead(A0);
  } while(prev >= lol);
  return prev;
}

void loop() {
  // put your main code here, to run repeatedly:
 int lol = analogRead(A0);
 if (lol < thresholdDown) {
  int loudness = 255;//50+min(205-(getMin(lol)*1), 0); // TODO: Parameter entsprechend adjusten #kommentaresindimmereinzeichenderunfähigkeit
  vol.tone(440, loudness); 
  vol.delay(100);
  //vol.tone(440, 0);
  vol.fadeOut(200);
  played = 1;
 } else if (lol >= thresholdUp && played == 1) {
  played = 0;
 }
 Serial.println(lol);
}
