#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char* ssid = "SSID";
const char* password = "password";
const long utcOffsetInSeconds = -18000;

#define RELAY 0 //Relay connected to GPIO0
#define ON 0 //Relay output is inverted
#define OFF 1
#define BUTTON 2
#define Morning 3
#define Evening 19

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() 
{
  Serial.begin(115200);
 
  pinMode(RELAY,OUTPUT);
  pinMode(BUTTON,INPUT);
  digitalWrite(RELAY, ON);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  timeClient.begin();

  digitalWrite(RELAY, OFF);
  delay(1000);
  digitalWrite(RELAY, ON);
  delay(1000);  
}
 
void loop() 
{

timeClient.update();
//Serial.println(timeClient.getFormattedTime());

if (timeClient.getHours() >= Morning && timeClient.getHours() < Evening) {
  digitalWrite(RELAY, OFF);
  Serial.println("Relay Off");
}

if (timeClient.getHours() >= Evening || timeClient.getHours() < Morning) {
  digitalWrite(RELAY, ON);
  Serial.println("Relay On");
}
delay(300000);
}
