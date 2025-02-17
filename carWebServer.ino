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
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homePage.h"

const char* ssid = "EnzosIphone";
const char* password = "12345678";

#define M1  14  // Motor 1 control pin (Direction)
#define E1  16  // Motor 1 enable pin (PWM for speed)
#define M2  5   // Motor 2 control pin (Direction)
#define E2  17  // Motor 2 enable pin (PWM for speed)

// PWM parameters
#define PWM_FREQ     5000 // Frequency for PWM
#define PWM_RES      8    // 8-bit resolution (0-255)
#define PWM_CHANNEL_E1 0  // PWM channel for Motor 1 (E1)
#define PWM_CHANNEL_E2 1  // PWM channel for Motor 2 (E2)

WebServer server(80);

//temp function to simulate temp sensor
//String getTemp() {
//  float temp = random(200, 301) / 10.0;
//  return String(temp, 2);
//}

void pwmControl()
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
}

void controlMotor1(int speed, bool forward) 
  {
    digitalWrite(M1, forward ? HIGH : LOW);  // Set direction
    ledcWrite(PWM_CHANNEL_E1, speed);       // Set speed
  }

// Function to control Motor 2
void controlMotor2(int speed, bool forward) 
  {
    digitalWrite(M2, forward ? HIGH : LOW);  // Set direction
    ledcWrite(PWM_CHANNEL_E2, speed);       // Set speed
  }

void getDistance()
  {
    server.send(200, "text/plain", bumperSensor());
  }

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

void setup(void) {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  server.on("/", handleRoot);
  server.on("/getDistance", getDistance);
  server.on("/controlMotor1", controlMotor1);
  server.on("/controlMotor2", controlMotor2);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(100);//allow the cpu to switch to other tasks
}