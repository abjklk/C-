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
int th=38;
int th1=300;

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
  lcd.setBacklight(255);

}

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  Serial.println(h);

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println(t);


  if (isnan(h) || isnan(t)) {
    Serial.println("nodata"); 
    lcd.println("Failed to read from DHT sensor!");
   return;
}
  // If the DHT-11 is not connected to correct pin or if it doesnt work no data will be sent
  root["temp"] = t;
  root["hum"] = h;
//  root["hi"] = hic;
  root["gasv"]= analogRead(A0);
  root["ldr"]= analogRead(A1);
  
  if(s.available()>0)
  {
    Serial.println("available esp8266");
    root.printTo(s);
  }
  dht_print();
  mq3_print();
  sendSms();  
    
}


void dht_print()
{
  lcd.home();
  lcd.clear();
  lcd.print("T=");
  lcd.print(root["temp"]);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H=");
  lcd.print(root["hum"]);
  lcd.print("%");
  delay(2000) ;
   if (root["hum"]>=th)
    {
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println ("Food  is Spoiled");
    }
    else
    {
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println ("Food  is Correct");
    }
    delay(1000);
}

void mq3_print()
{
   lcd.home();lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("MQ3=");
   lcd.print(root["gasv"]);
    delay(2000);
    if(root["gasv"]>th1)
    {
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println ("Food  is Spoiled");
    }
    else
    {
      lcd.home();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println ("Food  is Correct");
    }
    delay(1000);
}

void ldr_print()
{
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LDR=");
  lcd.print(root["ldr"]);
}

void sendSms()
{
      int f=0;
      String dataMessage;
      if(root["hum"]>th)
        f=1;
      delay(10);
      // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
      // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
      SIM900.println("AT + CMGS = \"+917892871157\"");
      delay(100);
      
      // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
      if(f)
       dataMessage = ("Temperature: " + String(root["temp"]) + "*C " + "\n" + " Humidity: " + String(root["hum"]) + "%" + "\n" + "MQ3 :" + String(root["gasv"]) + "\n" + "LDR :" + String(root["ldr"]) + "\n" + "Food Spoilt.");
      else
       dataMessage = ("Temperature: " + String(root["temp"]) + "*C " + "\n" + " Humidity: " + String(root["hum"]) + "%" + "\n" + "MQ3 :" + String(root["gasv"]) + "\n" + "LDR :" + String(root["ldr"]) + "\n" +"Food OK.");
      
      
      // Send the SMS text message
      SIM900.print(dataMessage);
      Serial.println(dataMessage);
      delay(100);
      // End AT command with a ^Z, ASCII code 26
      SIM900.println((char)26); 
      delay(1000);
//      SIM900.println();
      Serial.println("Done");
      // Give module time to send SMS
      delay(5000);  
  
  delay(10); 
  lcd.home();lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Message is sent ");
    delay(100);
  
}
