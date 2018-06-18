#include <Wire.h>
#include <Pixy.h>
#include <SPI.h>

#define X_CENTER ((PIXY_MAX_X-PIXY_MIN_X)/2)       
#define Y_CENTER ((PIXY_MAX_Y-PIXY_MIN_Y)/2)
#define MARGIN 0.3
#define STOP_WIDTH 200

#define FORWARD 0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3
#define BRAKE 4


Pixy pixy;

void print_info(char buf, Pixy pixy, uint16_t blocks){

    int j;  
    sprintf(buf, "Detected %d:\n", blocks);
    Serial.print(buf);
      
    for (j=0; j<blocks; j++){
        
      sprintf(buf, "  block %d: ", j);
      Serial.print(buf); 
      pixy.blocks[j].print();
   }
}

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Start...");
  pixy.init();
}

byte x = 0;

void loop() {

  static int i = 0;
  static int j;
  uint16_t blocks;
  char buf[32]; 
    
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if(blocks){

   // Serial.println("1");
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i % 2 == 0){

      //  Serial.println("1");
      // print_info(buf, pixy, blocks);

      for(j = 0; j < blocks; j++){
      
        if(pixy.blocks[j].signature == 1){

          if(pixy.blocks[j].x > (1 + MARGIN) * (int)X_CENTER){
            
            // print_info(buf, pixy, blocks);
            x = RIGHT;          
          }else if(pixy.blocks[j].x < (1 - MARGIN) * (int)X_CENTER){

            // print_info(buf, pixy, blocks);
            x = LEFT;
          }else if(pixy.blocks[j].width > STOP_WIDTH){

            //print_info(buf, pixy, blocks);
            x = BRAKE;
          }else{

            // print_info(buf, pixy, blocks);
            x = FORWARD;
          }
          
          Wire.beginTransmission(8); // transmit to device #8
          Wire.write(x);              // sends one byte
          Serial.println(x);
          Wire.endTransmission();
        }
      }
    }
  }  
  delay(100);
}
