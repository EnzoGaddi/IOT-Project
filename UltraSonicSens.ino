const int trigPin = 2;
const int echoPin = 19;

long duration;
float distanceCm;

void USSsetup() 
{
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void avoidCrash() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * 0.034/2;

  if(distanceCm <= 3 && distanceCm >=1)
  {
    while (distanceCm <= 3 && distanceCm >=1)
    {
      Serial.print("Too Close!!");
      Serial.print("\n");
      Serial.print("Distance (cm): ");
      Serial.println(distanceCm);
      Serial.print("\n");

     Serial.print("Braking!!");
     Serial.print("\n");
     
     slowDown();
     delay(3000);

     stop();
     delay(3000);

     Serial.print("Reversing...");
     Serial.print("\n");

     reverse();
     delay(3000);

     stop();
     delay(3000);

     Serial.print("Back to the Race!!");
     Serial.print("\n");
     Serial.print("\n");

     accelerate();
     delay(2000);

     avgSpeed();
     delay(3000);

      break;
    }
  }
  else
  {
    topSpeed();
  }
}