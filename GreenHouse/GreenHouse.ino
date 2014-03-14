/*
Greenhouse Controller
*/

#include <Servo.h> 

const int servoPin = 9;
const int sensorPin = 1;

int buttonState = 0;
int openTemp = 70; //80.0; //temp where we open the door 
bool doorOpen = false;

Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  servo.attach(servoPin); 
  Serial.begin(9600);
  open();
  close();

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

void close()
{
  // scan from 0 to 180 degrees
  for(angle = 10; angle < 170; angle++)  
  {                                  
    servo.write(angle);               
    delay(50);                   
  } 
}

void open()
{
  // now scan back from 180 to 0 degrees
  for(angle = 170; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(50);       
  }
}
