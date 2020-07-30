#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Wire.h>  
#include "SSD1306Wire.h"
#include "DHT.h"
#define DHTPIN D7     
#define DHTTYPE DHT11  
#define FIREBASE_HOST "safety-helmet.firebaseio.com"
#define FIREBASE_AUTH "Heg2ce8R0algZHDmbZlCEHJKdqTl77QU4aQ9q8HO"
#define WIFI_SSID "iot"
#define WIFI_PASSWORD "12345678"
FirebaseData firebaseData;
SSD1306Wire  display(0x3c, D2, D1);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  dht.begin();
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "IoT Based");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, "Safety ");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Helmet");
  display.display();
  delay(5000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Please Wait");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, "Connecting");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "to Network...");
  display.display();
  delay(5000);
  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Successfully");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, "Connected");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "to Network.");
  display.display();
  delay(5000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Please Wait");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, "Sensors are");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Initializing ...");
  display.display();
  delay(5000);
    
  }
int e=0;
String d;
int heartbeat;
void loop()
{ 
  float hm = dht.readHumidity();
  float tm = dht.readTemperature();
  int g = analogRead(0);
 int heartbeat = hb.read();
  Serial.println(hm);
  Serial.println(tm);
  Serial.println(heartbeat);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Body Temperature");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(tm));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "Celsius");
  display.display();
  delay(3000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Heartbeats");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(heartbeat));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "BPS");
  display.display();
  delay(3000);
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Outdoor Humidity");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(hm));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "%");
  display.display();
  delay(3000);
    display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Air Quality");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 16, String(g));
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 46, "PPM");
  display.display();
  delay(3000);
  Firebase.setString(firebaseData, "t",String(tm));
  Firebase.setString(firebaseData, "h",String(hm));
  Firebase.setString(firebaseData, "hb",String(heartbeat));
  Firebase.setString(firebaseData, "co",String(g));
  delay(3000);
}
