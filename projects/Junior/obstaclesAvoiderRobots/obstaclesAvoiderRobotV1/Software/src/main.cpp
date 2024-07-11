///////////////////////////////////////////////////////////////
///////////////// servo library config ////////////////////////
//////////////////////////////////////////////////////////////
#include<Servo.h>
Servo servo;

/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
///////////// ultrasonic library config /////////////////
/////////////////////////////////////////////////////////

  #define echoPin 5 // attach pin D2 Arduino to pin Echo of HC-SR04
  #define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
  long duration; // variable for the duration of sound wave travel
  int distance, distanceLeft, distanceRight; // variable for the distance measurement
  
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
//////////////// variables declaration ///////////////////
//////////////////////////////////////////////////////////
//pot 
  int potPin = A0;


int leftUp = 13 ,leftDown = 12 ,rightUp =  10,rightDown = 11;

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void setup() {
  //servo setup
    servo.attach(3);
  //////////////

  //ultra sonic setup  
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  ///////////////////

  //wheels setup
    DDRB = B111100;
  //////////////
  
  //serial setup
    Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  //////////////

  //
    Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
    Serial.println("with Arduino UNO R3");
    servo.write( 90 );
    delay(1000);  
  /////////////////
  //servo set forward
    servo.write(90);
}


void loop() {

  distance = ultrasonic();
  delay(30);
  if( distance > 10 )
    {
    
      forward();
    
    }
  else
    {
      stopWheels();
      
      servo.write(180);
      delay(400);
      distance  = ultrasonic();
      distanceRight = distance;
      delay(100);

      servo.write(0);
      delay(400);
      distance  = ultrasonic();
      distanceLeft = distance;
      delay(100);
      
      servo.write(90);
      delay(400);
      
      if(distanceLeft > distanceRight)
        {
          turnRight();
          delay(500);
          stopWheels();
        }
      else if(distanceLeft < distanceRight)
        {
            turnRight();
            delay(500);
            stopWheels();
        }
      //turnRight();
      //delay(500);
      //stopWheels();

      
      /*ultrasonic();
      if(distance < 30 )
        {
          turnRight();
          delay(500);
          stopWheels();
        }*/
    

    
    }
  //servo.write(90);
  //delay(500);  
  //servo.write(0);
  //delay(500);  
  //servo.write(180);
  //delay(500);
  
  
  
}


int ultrasonic(){
  int d;
   // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
    d = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(d);
    Serial.println(" cm");
  return d;  
}//END OF ultrasonic()

////////////////////////////////
void forward(){

  PORTB = B011000;
  
}//END OF forward()
void stopWheels(){

  PORTB = B000000;
  
}//END OF stopWheels()

void turnRight(){

  PORTB = B101000;
  
}//END OF stopWheels()
