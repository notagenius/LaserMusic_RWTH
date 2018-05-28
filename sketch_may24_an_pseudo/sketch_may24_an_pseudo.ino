#include "Volume.h"
// Include the Volume library -> scetch, Bibliothek einbinden, Bibliothek verwalten - neue bibliothek hinzufügen!

Volume vol;
int played = 0;
int thresholdDown;
int thresholdUp;

int generateMedium() {
  int res = 0;
  for (int i = 0; i < 100; i++) {
    int curr = analogRead(A0);
    res += curr/100;
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

void loop() {

  // here is the pseudo frequence id

  // put your main code here, to run repeatedly:

 int lol = analogRead(A0);

 // save 5-7 lol < treshDown (?)

 float M[5];   // save time measurement for identifing period time
 float MI[5]; // save measurement of current

float Delta_t;  // for identifying the oszillation threw time period
 
 int i=0;  // time reference 
 bool sign=true; //this is bool which tells if the period condition is fullfilled!
 while (sign==true) {
 if (lol < thresholdDown) {
  M[i]=time(thresholdDown); //existiert nicht

  if (i==1 && sign==true) {
  Delta_t=M[i]-M[i-1];
  sign=false;
  }
  

  vol.tone(440, 255);
  vol.delay(100);
  vol.tone(440,0);
  //  played = 1;

  i++;
  if (i>=5) {
  i=0;
  }
  //else if (lol >= thresholdUp && played == 1) {
  //played = 0;  }

  if (Delta_t!=M[i+1]-M[i]) {  // cyclic ie if i=5 -> i+1=0
    sign=false;  // condition to stop sound
  }
 }
 Serial.println(lol);
}

}
