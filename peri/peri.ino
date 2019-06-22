#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "jnubus-160d1.firebaseio.com"

TinyGPSPlus gps;
SoftwareSerial ss(4, 5); 

const char* ssid = "BirdsOfPassage";
const char* password = "iknownothing";
float latitude , longitude;

void setup()
{
  
  
  ss.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
 


  Firebase.begin(FIREBASE_HOST);


}

void loop()
{

  while (ss.available() > 0){
    if (gps.encode(ss.read()))
    {
      Serial.write("ss encode");
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        Firebase.setFloat ("buses/1/latitude" , latitude );
        Firebase.setFloat ("buses/1/longitude" , longitude );
      }
    }

  }
  delay(130);
}
