#include <IRremote.h>

const int irPin = 5;
const int enA = 6;
const int in1 = 7;
const int in2 = 8;

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
  Serial.begin(9600);
}
void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF629D: //Keypad button "VOL+"
      forward();
    }
    switch (results.value) {
      case 0xFFA857: //Keypad button "VOL-"
      rotate();
    }
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
      stopRobot();
    }
    irrecv.resume();
  }
}

void loop() {
  readRemote();
}

void stopRobot() {
  analogWrite(enA, 0);
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
}

void rotate() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);
}
