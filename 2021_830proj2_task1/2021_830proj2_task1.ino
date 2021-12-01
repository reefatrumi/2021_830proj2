#include <IRremote.h>
#include <Stepper.h>
#include <Servo.h>

const int irPin = 4;
const int servoPin = 6;


#define in1  11
#define in2  10
#define in3  9
#define in4  8

Stepper stepper(2048, in4, in2, in3, in1);
Servo servo;
IRrecv irrecv(irPin);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

int state = 1;
int stepVal = 0;

void setup() {
  pinMode(irPin, INPUT);
  irrecv.enableIRIn();
  stepper.setSpeed(5);
  servo.attach(6);
  servo.write(90);
  //Serial.begin(9600);
}
void loop() {
  readRemote();
  stepper.step(stepVal);

  if (state == 1) {
    stopRobot();
  }
  if (state == 2) {
    fwd();
  }
  if (state == 3) {
    rev();
  }
//  if (state == 4) {
//    left;
//  }
//  if (state == 5) {
//    right;
//  }
}
void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
        state = 1;
    }
    switch (results.value) {
      case 0xFF629D: //Keypad button "VOL+"
        state = 2;
    }
    switch (results.value) {
      case 0xFFA857: //Keypad button "VOL-"
        state = 3;
    }
    switch (results.value) {
      case 0xFF22DD: //Keypad button "FAST BACK"
        //state = 4;
        left();
    }
    switch (results.value) {
      case 0xFFC23D: //Keypad button "FAST FORWARD"
        //state = 5;
        right();
    }
    switch (results.value) {
      case 0xFF9867: //Keypad button "FAST FORWARD"
        //state = 5;
        center();
    }
    irrecv.resume();
  }
}

void stopRobot() {
  stepVal = 0;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void fwd() {
  stepVal = -1;
}

void rev() {
  stepVal = 1;
}

void left() {
  servo.write(110);
}

void right() {
  servo.write(70);
}

void center(){
  servo.write(90);
}
