/*
Greenhouse Controller
*/

#include <Servo.h> 

int servoPin = 9;
int sensorPin = 1;
int openTemp = 70; //80.0; //temp where we open the door 
bool doorOpen = false;

Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  servo.attach(servoPin); 
  Serial.begin(9600);
  //analogReference(EXTERNAL);
} 
 
 
void loop() 
{ 
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  
  Serial.print(voltage); Serial.println(" volts");
  
  float tempC = (voltage -.5) *100;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  Serial.print(tempC); Serial.println(" degrees C");
  Serial.print(tempF); Serial.println(" degrees F");
  
  if(doorOpen == true && tempF < openTemp)
  {
    close();
    doorOpen = false;
  }
  if(doorOpen == false && tempF >= openTemp)
  {
    open();
    doorOpen = true;
  }
 
  delay(1000); 
} 

void open()
{
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
}

void close()
{
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  }
}
