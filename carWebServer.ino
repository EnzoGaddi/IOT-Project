// This code is derived from the HelloServer Example 
// in the (ESP32) WebServer library .
//
// It hosts a webpage which has one temperature reading to display.
// The webpage is always the same apart from the reading which would change.
// The getTemp() function simulates getting a temperature reading.
// homePage.h contains 2 constant string literals which is the two parts of the
// webpage that never change.
// handleRoot() builds up the webpage by adding as a C++ String:
// homePagePart1 + getTemp() +homePagePart2 
// It then serves the webpage with the command:  
// server.send(200, "text/html", message);
// Note the text is served as html.
//
// Replace the code in the homepage.h file with your own website HTML code.
// 
// This example requires only an ESP32 and download cable. No other hardware is reuired.
// A wifi SSID and password is required.
// Written by: Natasha Rohan  12/3/23
//
#define USE_LITTLEFS

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homePage.h"
#include "FS.h"
#include <LittleFS.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define M1  27  // Motor 1 control pin (Direction)
#define E1  14  // Motor 1 enable pin (PWM for speed)
#define M2  5   // Motor 2 control pin (Direction)
#define E2  17  // Motor 2 enable pin (PWM for speed)

// PWM parameters
#define PWM_FREQ     5000 // Frequency for PWM
#define PWM_RES      8    // 8-bit resolution (0-255)
#define PWM_CHANNEL_E1 0  // PWM channel for Motor 1 (E1)
#define PWM_CHANNEL_E2 1  // PWM channel for Motor 2 (E2)

const char* ssid = "EnzosiPhone";
const char* password = "12345678";

const int trigPin = 2;
const int echoPin = 19;

long duration;
float distanceCm;

int fuelLevel = 100;

WebServer server(80);

void handleRoot() 
  {
    String message = homePagePart1;
    server.send(200, "text/html", message); // Send the HTML page
  }

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) 
{
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  //Configure PWM for E1 and E2 
  ledcAttach(PWM_CHANNEL_E1, PWM_FREQ, PWM_RES);
  ledcAttach(PWM_CHANNEL_E2, PWM_FREQ, PWM_RES);

  //Attach PWM channels to E1 and E2 pins
  ledcAttachChannel(E1, PWM_FREQ, PWM_RES, PWM_CHANNEL_E1);
  ledcAttachChannel(E2, PWM_FREQ, PWM_RES, PWM_CHANNEL_E1);

  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	// Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);

   if (!LittleFS.begin(true)) 
    {
        Serial.println("LittleFS mount failed!");
        return;
    }
    Serial.println("LittleFS mounted successfully!");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/distanceSensor", HTTP_GET, handleSensorRequest);
  server.on("/", handleRoot);
  server.on("/inline", []() 
  {
    server.send(200, "text/plain", "dis sensor works");
  });
  server.onNotFound(handleNotFound);

  server.on("/accelerationSensor", HTTP_GET, handleSensorRequest2);
  server.on("/", handleRoot);
  server.on("/inline", []() 
  {
    server.send(200, "text/plain", "accel sensor works");
  });
  server.onNotFound(handleNotFound);

  server.on("/LOGO-PERFORMANCE-CAR-ESTESO.png", HTTP_GET, []() {
    File file = LittleFS.open("/LOGO-PERFORMANCE-CAR-ESTESO.png", "r");
    if (!file) {
        server.send(404, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, "image/png");
    file.close();
});

server.on("/car.png", HTTP_GET, []() {
    File file = LittleFS.open("/car.png", "r");
    if (!file) {
        server.send(404, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, "image/png");
    file.close();
});

server.on("/car2.png", HTTP_GET, []() {
    File file = LittleFS.open("/car2.png", "r");
    if (!file) {
        server.send(404, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, "image/png");
    file.close();
});

server.on("/car3.png", HTTP_GET, []() {
    File file = LittleFS.open("/car3.png", "r");
    if (!file) {
        server.send(404, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, "image/png");
    file.close();
});

server.on("/Fuel.jpg", HTTP_GET, []() {
    File file = LittleFS.open("/Fuel.jpg", "r");
    server.streamFile(file, "image/jpeg");
    file.close();
});

server.on("/motor-stop", HTTP_POST, []() {
    brake();
  server.send(200, "text/plain", "Motor stopped!");
  });

server.on("/brake.jpg", HTTP_GET, []() {
    File file = LittleFS.open("/brake.jpg", "r");
    server.streamFile(file, "image/jpeg");
    file.close();
});

server.on("/motor-go", HTTP_POST, []() {
  if (fuelLevel > 0) 
  {
    go();
    server.send(200, "text/plain", "Motor moved!");
  } 
  else 
  {
    brake();
    server.send(200, "text/plain", "Out of fuel");
  }
  });

server.on("/accelerator.jpg", HTTP_GET, []() {
    File file = LittleFS.open("/accelerator.jpg", "r");  
    server.streamFile(file, "image/jpeg");
    file.close();
});

server.on("/fuelSystem", HTTP_POST, []() {
  fuel();
  server.send(200, "text/plain", "fuel hot");
  });

server.on("/refillFuel", HTTP_POST, []() {
  fuelLevel = 100;  
  server.send(200, "text/plain", "Fuel refilled");
});

server.on("/fuelSystem", HTTP_GET, []() {
  server.send(200, "text/plain", String(fuelLevel));
});

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}

String bumperSensor() 
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

    return String(distanceCm);
  }

void handleSensorRequest() 
  {
    String json = "{\"distance\": " + bumperSensor() + "}";
    server.sendHeader("Access-Control-Allow-Origin", "*");  // Allow fetch from other devices
    server.send(200, "application/json", json);
  }

String acceleratorSensor()
{
  if(mpu.getMotionInterruptStatus()) 
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    

    Serial.print("Acceleration:");
    return String(a.acceleration.x);
  }
  delay(10);
}

void handleSensorRequest2()
  {
    String json = "{\"acceleration\": " + acceleratorSensor() + "}";
    server.sendHeader("Access-Control-Allow-Origin", "*");  // Allow fetch from other devices
    server.send(200, "application/json", json);
  }

void go()
  {
    accelerate();
    delay(2000);
    avgSpeed();
    delay(2000);
    topSpeed();
  }

void brake()
  {
    slowDown();
    delay(2000);
    stop();
  }

void fuel()
  {
      if(fuelLevel > 0)
      {
        fuelLevel--;
      }
  }

