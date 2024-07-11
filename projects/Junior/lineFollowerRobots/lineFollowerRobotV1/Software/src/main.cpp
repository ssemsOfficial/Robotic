#include <Arduino.h>

////////////////////////////////////
/////////// variables //////////////
////////////////////////////////////
int   left_ir = 13,
      middle_ir = 12,
      right_ir = 11;
int   backward_rightMotor = 6,
      forward_rightMotor = 5,
      backward_leftMotor = 9,
      forward_leftMotor = 10;
char last_state = 'n';      

///////////////////////////////////
///////////////////////////////////
void turn_right();
void turn_left();
void stop_();

void setup() {

   pinMode(left_ir, INPUT); 
   pinMode(middle_ir, INPUT); 
   pinMode(right_ir, INPUT); 
   pinMode(forward_rightMotor, OUTPUT); 
   pinMode(backward_rightMotor, OUTPUT); 
   pinMode(forward_leftMotor, OUTPUT); 
   pinMode(backward_leftMotor, OUTPUT); 

   Serial.begin(9600);
  
}

void loop() {

 
  if( digitalRead(middle_ir)== 1 )
    {
     
      if( digitalRead(left_ir) == 0 && digitalRead(right_ir) == 0 ) // move forward   if >> 
        {
          
            analogWrite(forward_rightMotor, 100);
            digitalWrite(backward_rightMotor, LOW);
            analogWrite(forward_leftMotor, 100);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("move forward");
          
            
        }
      else if( digitalRead(left_ir) == 1 && digitalRead(right_ir) == 0 )//move left
        {
           
            analogWrite(forward_rightMotor, 100);
            digitalWrite(backward_rightMotor, LOW);
            analogWrite(forward_leftMotor, 70);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("move left");
           
        }
      else if( digitalRead(left_ir) == 0 && digitalRead(right_ir) == 1 )//move right
        {
           
            analogWrite(forward_rightMotor, 70);
            digitalWrite(backward_rightMotor, LOW);
            analogWrite(forward_leftMotor, 100);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("move right");
            
        }  
      
       
    }
  else if(digitalRead(middle_ir) == 0) // middle sensor not activated  or  missed up 
    { 
      if( digitalRead(left_ir) == 1 && digitalRead(right_ir) == 0 ) // turn left   if >> lef_ir = 1 and right_ir = 0
        {
          
            turn_left();
            last_state = 'f';
            
        }
      else if( digitalRead(left_ir) == 0 && digitalRead(right_ir) == 1 ) // turn right   if >> right left_ir = 0 and right_ir = 1
        {
            turn_right();
            last_state = 'r';
        }
      else if( digitalRead(left_ir) == 0 && digitalRead(right_ir) == 0 ) // stop  if >> right left_ir = 0 and right_ir = 0
        {
          
            switch(last_state)
              {
                  case 'r':
                      while( digitalRead(right_ir) == 0 )
                          turn_right();
                      break;
                  case 'f':
                      while( digitalRead(left_ir) == 0 )
                          turn_left();
                      break; 
                  case 'n':
                          stop_();
                      break; 
                  default:
                      break;              
              }
          
            
        }
      
    }
    
    delay(10);
  
           
 
}

void turn_right(){

            digitalWrite(forward_rightMotor, LOW);
            digitalWrite(backward_rightMotor, LOW);
            analogWrite(forward_leftMotor, 200);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("turn right");
}

void turn_left(){
            analogWrite(forward_rightMotor, 200);
            digitalWrite(backward_rightMotor, LOW);
            digitalWrite(forward_leftMotor, LOW);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("turn left");
}

void stop_(){
            digitalWrite(forward_rightMotor, LOW);
            digitalWrite(backward_rightMotor, LOW);
            digitalWrite(forward_leftMotor, LOW);
            digitalWrite(backward_leftMotor, LOW);
            Serial.println("turn left");
}
