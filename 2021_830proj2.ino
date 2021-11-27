#include <IRremote.h>

const int enA = 9;
const int in1 = 8;
const int in2 = 7;
const int irPin = 12;

int state = 3;
IRrecv irrecv(irPin);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() {
  pinMode(irPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  irrecv.enableIRIn();
  //Serial.begin(9600);
}
void loop() {
  readRemote();
  if(state == 1){
    forward();
  }
  if(state == 2){
    rotate();
  }
  if(state == 3){
    stopRobot();
  }
  Serial.println(state); 
}
void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF629D: //Keypad button "VOL+"
      state = 1;
      Serial.println("moving forward");
    }
    switch (results.value) {
      case 0xFFA857: //Keypad button "VOL-"
      state = 2;
      Serial.println("rotating");
    }
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
      state = 3;
      Serial.println("stopped");
    }
    irrecv.resume();
  }
}



void stopRobot() {
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

void rotate() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
}
