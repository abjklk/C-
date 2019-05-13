//arduino
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
SoftwareSerial s(5,6);
SoftwareSerial SIM900(9,10);
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x27);
int show;

void setup() {
    int error;
  s.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  dht.begin();
  Serial.begin(9600);
  SIM900.begin(19200);
  
  delay(2000);
  Serial.print("SIM900 ready...");

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);
  if (error == 0) 
  {
    Serial.println(": LCD found.");
  } 
  else 
  {
    Serial.println(": LCD not found.");
  }
  lcd.begin(16, 2);  
  show = 0;

}

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {
  
  float h = dht.readHumidity();
  Serial.println(h);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println(t);
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  Serial.println(f);
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  Serial.println(hif);
  
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("nodata"); 
   return;
}
  // If the DHT-11 is not connected to correct pin or if it doesnt work no data will be sent
  root["temp"] = t;
  root["hum"] = h;
  root["hi"] = hic;
  root["gasv"]= analogRead(A0);
  
  if(s.available()>0)
  {
    Serial.println("available");
    root.printTo(s);
  }
}
