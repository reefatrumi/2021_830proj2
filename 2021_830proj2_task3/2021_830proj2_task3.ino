#include <IRremote.h>
#include <Stepper.h>
#include <Servo.h>

const int irPin = 4;
const int servoPin = 6;
const int trig = 7;
const int echo = 5;

#define in1  11
#define in2  10
#define in3  9
#define in4  8

Stepper stepper(2048, in4, in2, in3, in1);
Servo servo;
IRrecv irrecv(irPin);
decode_results results;

int cycle = 2048;
double distance;
long duration;
int start = 0;
int stepCounter = 0;
int toggle = 0;
void setup() {
  pinMode(irPin, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  irrecv.enableIRIn();
  stepper.setSpeed(10);
  servo.attach(6);
  servo.write(88);
  Serial.begin(9600);
}
void loop() {
  readRemote();
  calculateDist();
  if (start == 1 && stepCounter < 3.7 * cycle) {
    if (distance <= 30 && toggle != 1) {
      stepCounter = stepCounter + 3000;
      avoid();
      distance = 100;
      toggle = 1;
    }
    stepper.step(-10);
    stepCounter = stepCounter + 10;
  }
  stopRobot();
}

void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
        start = 1;
    }
    irrecv.resume();
  }
}
void calculateDist() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0344 / 2;
  Serial.println(distance);
}
void avoid() {
  left();
  stepper.step(-0.5 * cycle);
  right();
  stepper.step(-0.5 * cycle);
  center();
  stepper.step(-0.5 * cycle);
  right();
  stepper.step(-0.5 * cycle);
  left();
  stepper.step(-0.5 * cycle);
  center();
  distance = 100;
}

void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void left() {
  servo.write(110);
}

void right() {
  servo.write(70);
}

void center() {
  servo.write(90);
}
