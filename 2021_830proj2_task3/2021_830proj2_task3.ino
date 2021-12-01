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
  if (start = 1 && stepCounter < 9.3 * cycle) {
    if (distance <= 50) {
      stepCounter = stepCounter + 200;
      avoid();
    }
    stepper.step(-1);
    stepCounter++;
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

void avoid() {
  right();
  stepper.step(-0.2 * cycle);
  left();
  stepper.step(-0.4 * cycle);
  right();
  stepper.step(-0.2 * cycle);
  center();
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
