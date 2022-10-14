#include <Servo.h>
Servo myservo;
const int Lin = 10, Rin = 12, Lout = 11, Rout = 13, serv = 9; //setting sensor pins and servo pin

// establish variables for duration
// and the distance result in inches
long Rduration, Lduration, Rinches, Linches;

int threshold = 10; //Sensor threshold in inches

int angle = 80; //Initial angle


boolean debug = false;



void setup() {
  
  if (debug)
  { Serial.begin(9600); }
  myservo.attach(9);  //attach servo to pin 9
  }


void loop()
{ 
   
  //I modified it for a 4 pin sensor as oppsed to the 3 pin sensor 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  pinMode(Rout, OUTPUT);
  digitalWrite(Rout, LOW);
  delayMicroseconds(2);
  digitalWrite(Rout, HIGH);
  delayMicroseconds(5);
  digitalWrite(Rout, LOW);
  
Rduration = pulseIn(Rin, HIGH); 

pinMode(Lout, OUTPUT);
digitalWrite(Lout, LOW);
delayMicroseconds(2);
digitalWrite(Lout, HIGH);
delayMicroseconds(5);
digitalWrite(Lout, LOW);


Lduration = pulseIn(Lin, HIGH);


// convert the time into a distance
Rinches = microsecondsToInches(Rduration);  // microsecondsToInches Funtion that convert Rduration to inches 
Linches = microsecondsToInches(Lduration);  // microsecondsToInches Funtion that convert Lduration to inches 


if (debug) // This function to debuging and write in file this movements and inches 
{
  Serial.print("Left: ");
  Serial.print(Linches);
  Serial.println(" in");
  Serial.print("Right: ");
  Serial.print(Rinches);
  Serial.println(" in"); 
 } 
 
 follow(); // follow function define in below 
 
 }
long microsecondsToInches(long microseconds) { 

return microseconds / 74 / 2; }

void follow()
{
  if (Linches <= threshold || Rinches <= threshold) 
    { 
      
        if (Linches + 2 < Rinches)
           { angle = angle - 2; }
           
        if (Rinches + 2 < Linches) 
            { angle = angle + 2; } 
     } 
  
           if (angle > 160) 
                { angle = 160; } // the max angle in the right 
            if (angle < 0)
                 { angle = 0; } // the min angle that servo Turn it over
  
         myservo.write(angle); // write the current angle to begin with second round of the loop 
  
  }
