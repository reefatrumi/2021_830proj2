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
IRrecv irrecv(irPin);    
decode_results results;    

int cycle = 2048;

void setup() {
  pinMode(irPin, INPUT);
  irrecv.enableIRIn();
  stepper.setSpeed(10);
  servo.attach(6);
  servo.write(88);

}
void loop() {
  readRemote();
}

void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
        auton();
    }
    switch (results.value) {
      case 0xFFA25D: //Keypad button "PAUSE"
        stopRobot();
    }
    irrecv.resume();
  }
}

void auton() {
  stepper.step(-1.75 * cycle);
  right();
  stepper.step(-1 * cycle);
  center();
  stepper.step(-0.8 * cycle);
  left();
  stepper.step(-0.9 * cycle);
  center();
  stepper.step(-1.4 * cycle);
  stopRobot();

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
