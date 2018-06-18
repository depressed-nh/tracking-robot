#include <Wire.h>
#define SPEED 200
#define DELAY 100

#define FORWARD 0
#define BACKWARD 1 
#define LEFT 2
#define RIGHT 3
#define BRAKE 4

#define PIN_MOTOR_A 12
#define BRAKE_MOTOR_A 9
#define PIN_MOTOR_B 13
#define BRAKE_MOTOR_B 8
#define PIN_SPEED_A 3
#define PIN_SPEED_B 11

void move_backward(){
  
  digitalWrite(PIN_MOTOR_A, HIGH);
  digitalWrite(BRAKE_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, HIGH);
  digitalWrite(BRAKE_MOTOR_B, LOW);
  analogWrite(PIN_SPEED_A, SPEED);
  analogWrite(PIN_SPEED_B, SPEED);
  delay(DELAY);
}

void move_forward(){
  
  digitalWrite(PIN_MOTOR_A, LOW);
  digitalWrite(BRAKE_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, LOW);
  digitalWrite(BRAKE_MOTOR_B, LOW);
  analogWrite(PIN_SPEED_A, SPEED);
  analogWrite(PIN_SPEED_B, SPEED);
  delay(DELAY);
}

void brake(){

  digitalWrite(BRAKE_MOTOR_A, HIGH);
  digitalWrite(BRAKE_MOTOR_B, HIGH);
}

void turn_left(){

  digitalWrite(PIN_MOTOR_A, HIGH);
  digitalWrite(BRAKE_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, LOW);
  digitalWrite(BRAKE_MOTOR_B, LOW);
  analogWrite(PIN_SPEED_A, SPEED);
  analogWrite(PIN_SPEED_B, SPEED);
  delay(DELAY);
}

void turn_right(){

  digitalWrite(PIN_MOTOR_A, LOW);
  digitalWrite(BRAKE_MOTOR_A, LOW);
  digitalWrite(PIN_MOTOR_B, HIGH);
  digitalWrite(BRAKE_MOTOR_B, LOW);
  analogWrite(PIN_SPEED_A, SPEED);
  analogWrite(11, SPEED);
  delay(DELAY);
}

void setup() {
  // Motor B
  pinMode(PIN_MOTOR_B, OUTPUT);
  pinMode(BRAKE_MOTOR_B, OUTPUT);

  // Motor A
  pinMode(PIN_MOTOR_A, OUTPUT);
  pinMode(BRAKE_MOTOR_A, OUTPUT);
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output  
  Serial.println("Starting...");
}

void loop() {
  delay(15);
}

void receiveEvent(int howMany) {
  brake();
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int instruction = Wire.read();    // receive byte as an integer
  Serial.println(instruction);         // print the integer

//moves
  switch(instruction){
    case FORWARD:
      move_forward();
      break;
      
     case BACKWARD:
      move_backward();
      break;
      
     case LEFT:
      turn_left();
      break;
      
     case RIGHT:
      turn_right();
      break;
      
     case BRAKE:
      brake();
      break;  
  }
  
}

