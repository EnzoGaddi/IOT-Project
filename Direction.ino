void accelerate()
{
  controlMotor1(200, true);
  controlMotor2(200, true);
}

void avgSpeed()
{
  controlMotor1(220, true);
  controlMotor2(220, true);
}

void topSpeed()
{
  controlMotor1(255, true);
  controlMotor2(255, true);
}

void reverse()
{
  controlMotor1(200, false);
  controlMotor2(200, false);

  delay(2000);

  controlMotor1(220, false);
  controlMotor2(220, false);
}

void stop()
{
  digitalWrite(M1, LOW);  // No direction for Motor 1
  digitalWrite(M2, LOW);  // No direction for Motor 2
  ledcWrite(PWM_CHANNEL_E1, 0); // Stop Motor 1
  ledcWrite(PWM_CHANNEL_E2, 0); // Stop Motor 2
}

void slowDown()
{
  controlMotor1(220, true);
  controlMotor2(220, true);

  delay(2000);

  controlMotor1(200, true);
  controlMotor2(200, true);
}