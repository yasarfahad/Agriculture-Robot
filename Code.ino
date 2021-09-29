#include <SoftwareSerial.h>
#include<AFMotor.h>
#include<Servo.h>
#include <NewPing.h>
 
#define TRIG_PIN A4 
#define ECHO_PIN A2 
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 600cm
#define COLL_DIST 50 // sets distance at which robot stops 


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor m1(1); // water
AF_DCMotor m2(2); // left motor
AF_DCMotor m3(3); // right motor
AF_DCMotor m4(4); // drill
Servo posServo; // Moisture Sensor
Servo slidServo; // Seeding
int curDist;
int command;

void setup() {

slidServo.attach(9);
posServo.attach(10);
Serial.begin(9600);
m1.setSpeed(255);
m2.setSpeed(255);
m3.setSpeed(255);
m4.setSpeed(200);
}

void loop() {
command = Serial.read();

                                        /*     Manual    */

if(command >=1 && command <=179)   //pos servo move according to the thumb position on the mob app between 1 -- 179  .
{
  posServo.write(command);
}
else if (command == 210)    //slidservo Move To Angle 40
{
  slidServo.write(40);
}
else if (command == 211)    //slid movw to angle 90
{
  slidServo.write(90);  
}
else if (command == 200) //Forward
{
  m2.run(FORWARD);
  m3.run(FORWARD);
}
else if(command == 202) // turn right
{
  m2.run(FORWARD);
  m3.run(BACKWARD);  
}
else if(command == 209) // Stop all motor
{
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);  
}
else if(command == 201) //turn left
{
  m2.run(BACKWARD);
  m3.run(FORWARD);  
}
else if(command == 203) // backward
{
  m2.run(BACKWARD);
  m3.run(BACKWARD);  
}
else if(command == 0) // stop m2&m3 motor
{
  m2.run(RELEASE);
  m3.run(RELEASE);  
}

else if (command == 207) // water on
{
  m1.run(FORWARD);
 
}
else if(command == 208) // water off
{
 
  m1.run(RELEASE);  
}
else if(command == 204) // drill forward
{
  
  m4.run(FORWARD);
}

else if(command == 205) // drill backward
{
  
  m4.run(BACKWARD);  
}
else if(command == 206) // drill stop
{
  m4.run(RELEASE);
    
}
else if (command == 212) // Automatic
{
    curDist = readPing();
    delay(500);
 Serial.println(curDist);
   while (curDist < COLL_DIST) // >
  {
   
  Serial.println("AUTOMATIC MODE ACTIVATED");
   m2.run(FORWARD);
  m3.run(FORWARD);
  delay(1000);
  m2.run(RELEASE);
  m3.run(RELEASE);
  delay(3000);
  m4.run(BACKWARD);
  delay(2000);
  m4.run(FORWARD);
  delay(2000);
  m4.run(RELEASE);
  slidServo.write(70);
  delay(900);
  slidServo.write(0);
  delay(100);
  posServo.write(40);
  delay(150);
  posServo.write(90);  
  delay(150);
  
  int sensorValue=analogRead(A3);
  Serial.println(sensorValue);
  if(sensorValue>=800)
  {
    m1.run(FORWARD);
  delay(2000);
  m1.run(RELEASE);
  delay(500);
  }
  else if(sensorValue >500 && sensorValue < 800)
  {
  m1.run(FORWARD);
  delay(1000);
  m1.run(RELEASE);
  delay(500);
      
      }
       curDist = readPing();
       delay(500);
 Serial.println(curDist);
  }
     //else if (curDist > COLL_DIST)   // <
     {
    m1.run(RELEASE);
    m2.run(RELEASE);
    m3.run(RELEASE);
    m4.run(RELEASE);
    digitalWrite(12, !digitalRead(12));
    delay(2000);
     
}
}
}
  int readPing() { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
   }
