//RC car with ultrasonic sensor

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLg8X9QnHz"
#define BLYNK_TEMPLATE_NAME "ESP32 IOT"
#define BLYNK_AUTH_TOKEN "r3s7yIc6dYoexAJH6zKwqruRigVkrS_9"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Chaitanya";
char pass[] = "cHaitanya@45";

// ultrasonic sensor
const int trigPin = 32;
const int echoPin = 33;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
int distance;

// Motor A
//   int motor1Pin1 = 27; 
//   int motor1Pin2 = 26; 
//   int enable1Pin = 14; 

// // Motor A
//   int motor1Pin3 = 33; 
//   int motor1Pin4 = 32; 
//   int enable1Pin2 = 35; 

// Setting PWM properties
// const int freq = 30000;
// const int pwmChannel = 0;
// const int pwmChannel2 = 1;
// const int resolution = 8;
// int dutyCycle = 200;

// BLYNK_WRITE(V1) { //move forward  
//   // ledcWrite(pwmChannel, 500);
//   // ledcWrite(pwmChannel2, 500);
//   digitalWrite(motor1Pin1, HIGH);
//   digitalWrite(motor1Pin2, LOW);

//   digitalWrite(motor1Pin3, HIGH);
//   digitalWrite(motor1Pin4, LOW);
// }

// BLYNK_WRITE(V2) { //move backward
//   // ledcWrite(pwmChannel, 500);
//   // ledcWrite(pwmChannel2, 500);
//   digitalWrite(motor1Pin1, LOW);
//   digitalWrite(motor1Pin2, HIGH);

//   digitalWrite(motor1Pin3, LOW);
//   digitalWrite(motor1Pin4, HIGH);
// }

// BLYNK_WRITE(V3) { // turn left
//   // ledcWrite(pwmChannel, 500);
//   // ledcWrite(pwmChannel2, 500);
//   digitalWrite(motor1Pin1, LOW);
//   digitalWrite(motor1Pin2, HIGH);

//   digitalWrite(motor1Pin3, HIGH);
//   digitalWrite(motor1Pin4, LOW);
// }

// BLYNK_WRITE(V4) { // turn right
//   // ledcWrite(pwmChannel, 500);
//   // ledcWrite(pwmChannel2, 500);
//   digitalWrite(motor1Pin1, HIGH);
//   digitalWrite(motor1Pin2, LOW);

//   digitalWrite(motor1Pin3, LOW);
//   digitalWrite(motor1Pin4, HIGH);
// }

// BLYNK_WRITE(V5) { // stop
//   // Stop the DC motor
//   digitalWrite(motor1Pin1, LOW);
//   digitalWrite(motor1Pin2, LOW);

//   digitalWrite(motor1Pin3, LOW);
//   digitalWrite(motor1Pin4, LOW);
// }

void measureDistance(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

  Blynk.virtualWrite(V0, (String(distance) + " cm"));
}

void setup()
{
  // Debug console
  // Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // pinMode(motor1Pin1, OUTPUT);
  // pinMode(motor1Pin2, OUTPUT);
  // pinMode(enable1Pin, OUTPUT);

  // pinMode(motor1Pin3, OUTPUT);
  // pinMode(motor1Pin4, OUTPUT);
  // pinMode(enable1Pin2, OUTPUT);

  // configure LED PWM functionalitites
  // ledcSetup(pwmChannel, freq, resolution);
  // ledcSetup(pwmChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  // ledcAttachPin(enable1Pin, pwmChannel);

  // ledcAttachPin(enable1Pin2, pwmChannel2);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // testing
  // Serial.print("Testing DC Motor...");
}

void loop()
{   
    delay(1000);
    measureDistance();

    Blynk.run();

  
}