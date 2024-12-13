#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

void ACC_setup() 
{
  Serial.begin(115200);
  while(!Serial)
  delay(10);
  
  if(!mpu.begin()){
    while(1){
      delay(10);
    }
  }

  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);
}

void ACC_loop() 
{
  if(mpu.getMotionInterruptStatus())
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Acceleration:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("\n");

    Serial.print("Gyro:");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print("\n");
  }
  delay(10);
}


