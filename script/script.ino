#include <MovementControl.h>
#include <IRSensorMotorListener.h>

const int rightMotorFwd = 6;
const int rightMotorBck = 5;
const int leftMotorFwd = 9;
const int leftMotorBck = 10;
const int leftSensor = 8;
const int rightSensor = 7;
MovementControl movementControl = MovementControl(6, 5, 10, 9);
IRSensorControl sensorControl = IRSensorControl(7, 8);
IRSensorMotorListener motorListener = IRSensorMotorListener(&movementControl);
char s[256];

void setup() {
  // put your setup code here, to run once:
  movementControl.setDirection(Direction::FORWARD);
  movementControl.setSpeed(6);
  sensorControl.addListener(&motorListener);
}

void loop() {
  // Print out the current stats on the motor
  // This takes up large amount of memory so remove when we are done
  Serial.begin(115200);
  //Serial.print(movementControl.toString(s, 256));
  memset(s, 0, sizeof(s));
  //Serial.println();
  Serial.print(motorListener.toString(s, 256));
  //memset(s, 0, sizeof(s));
  Serial.println();
  Serial.println();
  
  // put your main code here, to run repeatedly:
  sensorControl.readSensors();
  delay(10);
}

