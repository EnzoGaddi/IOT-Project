// Define ESP32 outputs to the motor driver pins
#define M1  5   // Motor 1 control pin (Direction)
#define E1  17  // Motor 1 enable pin (PWM for speed)
#define M2  14  // Motor 2 control pin (Direction)
#define E2  27  // Motor 2 enable pin (PWM for speed)

// PWM parameters
#define PWM_FREQ     5000 // Frequency for PWM
#define PWM_RES      8    // 8-bit resolution (0-255)
#define PWM_CHANNEL_E1 0  // PWM channel for Motor 1 (E1)
#define PWM_CHANNEL_E2 1  // PWM channel for Motor 2 (E2)

void setup() 
{
  // Set M1 and M2 as output for direction control
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  // Configure PWM for E1 and E2
  ledcAttach(PWM_CHANNEL_E1, PWM_FREQ, PWM_RES);
  ledcAttach(PWM_CHANNEL_E2, PWM_FREQ, PWM_RES);

  // Attach PWM channels to E1 and E2 pins
  ledcAttachChannel(E1, PWM_FREQ, PWM_RES, PWM_CHANNEL_E1);
  ledcAttachChannel(E2, PWM_FREQ, PWM_RES, PWM_CHANNEL_E2);

  USSsetup();
  ACCsetup();
}

// Function to control Motor 1
void controlMotor1(int speed, bool forward) {
  digitalWrite(M1, forward ? HIGH : LOW);  // Set direction
  ledcWrite(PWM_CHANNEL_E1, speed);       // Set speed
}

// Function to control Motor 2
void controlMotor2(int speed, bool forward) {
  digitalWrite(M2, forward ? HIGH : LOW);  // Set direction
  ledcWrite(PWM_CHANNEL_E2, speed);       // Set speed
}

void loop() 
{
  forward();
  USSloop();
  ACCloop();
}
