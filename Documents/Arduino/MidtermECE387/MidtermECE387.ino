
#include <Servo.h> 

Servo motor; 

int red = 8;
int yellow = 13;

long duration, cm;
int trig = 12;
int echo = 9;
int state = 0;
int theta = 1;


void setup() { 
  Serial.begin(9600);
  motor.attach(7); 
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
 } 
 
 
void loop() { 

// Checks the position and changes states
 if (theta <= 1)
 	state = 0;
    
 if (theta >= 180)
 	state = 1;

  // Checks the state and moves the position of the servo motor
 if (state == 0)
 	theta = theta+1;
    
 if (state == 1)
    	theta = theta-1;

  // Moves the motor
  motor.write(theta);

  // sets output on as 8 sonic bursts are sent
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // receives the bursts
  pinMode(echo, INPUT);
  // records the distance based on time
  duration = pulseIn(echo, HIGH);
  
  cm = microsecondsToCentimeters(duration);  
  
  if (cm > 300)
    cm = 300; 

  if (cm <= 10){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
  } else {
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  }
  Serial.print(theta); 
  Serial.print(" "); 
  Serial.println(cm);
  delay(50);
  
} 

long microsecondsToCentimeters(long microseconds) { return microseconds / 29 / 2; }


