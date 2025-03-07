#include <AFMotor.h>
#include <Servo.h>
AF_DCMotor motor(4); 
Servo myservo;
int pos = 0;
const int trigPin = A1;  
const int echoPin = A0;
int dir=0;
unsigned long start;
int timpManevra;
bool manevra=false;
void setup() 
{
	//Set initial speed of the motor & stop
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
	motor.setSpeed(250);
	motor.run(RELEASE);
  myservo.attach(9); 
  myservo.write(65); 
  //  myservo.write(55); stanga
  // myservo.write(75); 
}

void startManevra(int time){
  manevra=true;
  timpManevra=time;
  start=millis();
}

void verificareManevra(){
  int a=millis()-start;
  if(a>timpManevra){
    manevra=false;
  }
}


void loop() 
{
  float distance=getDist(echoPin);
  Serial.println(distance);
  if(distance>30){
    motor.run(FORWARD);
  }else if(distance<10){
     motor.run(BACKWARD);
  }else{
    motor.run(RELEASE);
  }
  
}






float getDist(int echoPn){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPn, HIGH);
  float distance = (duration*.0343)/2;
  return distance;
}