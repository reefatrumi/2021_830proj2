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

int cycle = 2048;

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
}

void readRemote() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFF02FD: //Keypad button "PAUSE"
        auton();
    }
    irrecv.resume();
  }
}

void auton(){
  stepper.step(-4.5*cycle);
  right();
  stepper.step(-0.2*cycle);
  center();
  stepper.step(-4.3*cycle);
  right();
  stepper.step(-0.2*cycle);
  center();
  stepper.step(-4.3*cycle);
  right();
  stepper.step(-0.2*cycle);
  center();  
  stepper.step(-4.3*cycle);
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

void center(){
  servo.write(90);
}
