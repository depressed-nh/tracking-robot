#include <Wire.h>
#define SPEED 200
#define DELAY 100

void move_backward(){
  
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(3, SPEED);
  analogWrite(11, SPEED);
  delay(DELAY);
}

void move_forward(){
  
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(3, SPEED);
  analogWrite(11, SPEED);
  delay(DELAY);
}

void brake(){

  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}

void turn_left(){

  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(3, SPEED);
  analogWrite(11, SPEED);
  delay(DELAY);
}

void turn_right(){

  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(3, SPEED);
  analogWrite(11, SPEED);
  delay(DELAY);
}

void setup() {
  // Motor B
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  // Motor A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output  
  Serial.println("Starting.....");
}

void loop() {
  delay(15);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  brake();
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

//moves
  switch(x){
    case 0:
      move_forward();
      break;
      
     case 1:
      move_backward();
      break;
      
     case 2:
      turn_left();
      break;
      
     case 3:
      turn_right();
      break;
      
     case 4:
      brake();
      break;  
  }
  
}

