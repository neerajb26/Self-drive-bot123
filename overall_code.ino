#include <TinyGPSPlus.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <WiFi.h>

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
char ssid[] = "ssid";
char pass[] = "pass";

// The TinyGPSPlus object
TinyGPSPlus gps;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

float head_to_lat = 17.581651;
float head_to_lan = 78.121667;
float compass_heading;

void getcompass(){
  sensors_event_t event; 
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.0098960169;
  heading += declinationAngle;
  if(heading < 0)
      heading += 2*PI;
      
    // Check for wrap due to addition of declination.
  if(heading > 2*PI)
     heading -= 2*PI;
     
  // Convert radians to degrees for readability.
  compass_heading = heading * 180/M_PI; 
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
   //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

}
void loop() {
     Blynk.run();
  //updateSerial();
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
    {
      displayInfo();
      gps_info();
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true)
      ;
  }
  delay(1000);
}
int number_of_stats = 0;
unsigned long Distance_To_Home;
unsigned long courseToDestination;
void gps_info()
{
   //Number_of_SATS = (int)(gps.satellites.value());         //Query Tiny GPS for the number of Satellites Acquired 
        Distance_To_Home = TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(), head_to_lat, head_to_lan);
        courseToDestination = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), head_to_lat, head_to_lan );
          //Query Tiny GPS for Distance to Destination    
        Serial1.print("Lat:");
        Serial1.print(gps.location.lat(),6);
        Serial1.print(" Lon:");
        Serial1.print(gps.location.lng(),6);
        Serial1.print(" ");
        //Serial1.print(Number_of_SATS); 
        Serial1.print(" SATs ");
        Serial1.print(Distance_To_Home);
        Serial1.print("m"); 
        getcompass();
        Serial.print("compass h : ");
        Serial.println(compass_heading);
        Serial.print("Distance to Home ");
        Serial.println(Distance_To_Home);
        Serial.print("diff: ");
        int a = (courseToDestination - compass_heading) ; 
        Serial.println(a);
        int x = (courseToDestination - 360);
        int y = (compass_heading - x) ;
        int z = (y -360) ;
        Serial.print("Z : ");
        Serial.println(z);
        delay(1000);
}
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.println();
    Blynk.virtualWrite(V5, String(latitude, 6));
    Blynk.virtualWrite(V8, String(longitude, 6));
  }
  else
  {
    Serial.print(F("INVALID\n"));
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());  //Forward what Software Serial received to Serial Port
  }
}