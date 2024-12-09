void forward()
{
//25%
  controlMotor1(127, true);
  controlMotor2(127, true);

//50% speed
  controlMotor1(255, true);
  controlMotor2(255, true);

//100% speed
  controlMotor1(510, true);
  controlMotor2(510, true);
}

void stop() 
{
  digitalWrite(M1, LOW);  // No direction for Motor 1
  digitalWrite(M2, LOW);  // No direction for Motor 2
  ledcWrite(PWM_CHANNEL_E1, 0); // Stop Motor 1
  ledcWrite(PWM_CHANNEL_E2, 0); // Stop Motor 2
}

void reverse()
{
  controlMotor1(127, false);
  controlMotor2(127, false);
  delay(3000);

//backward at full speed
  controlMotor1(255, false);
  controlMotor2(255, false);
}

void right()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  ledcWrite(PWM_CHANNEL_E1, 1); 
  ledcWrite(PWM_CHANNEL_E2, 1);
}

void left()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  ledcWrite(PWM_CHANNEL_E1, 1); 
  ledcWrite(PWM_CHANNEL_E2, 1);
}

void slow()
{
  controlMotor1(255, true);
  controlMotor2(255, true);
  delay(2000);

  controlMotor1(127, true);
  controlMotor2(127, true);
}