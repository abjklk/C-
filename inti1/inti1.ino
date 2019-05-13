#include <Adafruit_Sensor.h>
//Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
DHT dht(8, DHT11);
#define MQ3_PIN A0
int gas_read = 0;
#define LDR_PIN A1
int ldr_read = 0;
int th=38;
int th1=300;

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int show;
float t=0;
float h=0;
float f=0;
float mq;
float ldr1;
#define DHTPIN 8
char data = 0;
void dht11();
void mq3();
void ldr();
void gsm();
boolean readData();
void sendSms();

SoftwareSerial SIM900(9,10);

char incomingChar;

void setup()
{
  int error;
  Serial.begin(19200); 
  SIM900.begin(19200);

  delay(2000);
  Serial.print("SIM900 ready...");

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);


  Serial.println("LCD...");
  while (! Serial);
  Serial.println("Dose: check for LCD");
  // See http://playground.arduino.cc/Main/I2cScanner
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
  } // if

  lcd.begin(16, 2); // initialize the lcd
  show = 0;
} // setup()

void loop()
{  
  if (show == 0) 
  {
    lcd.setBacklight(255);
    lcd.home(); lcd.clear();
    dht11();
    delay(1000);
    lcd.setBacklight(255);

  } 
  else if (show == 1) 
  {
    lcd.home();lcd.clear();
    lcd.setCursor(0,0);
    mq3();
    delay(1000);
    lcd.setBacklight(255);
  } 
  else if (show == 2) 
  {
    lcd.home();lcd.clear();
    lcd.setCursor(0,0);
    ldr();
    delay(1000);
    lcd.setBacklight(255);
  } 
  else if (show == 3) 
  {
    sendSms();  
    lcd.home();lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Message is sent ");
    delay(100);
    lcd.setBacklight(255);
  } 
    delay(100);
    show = (show + 1) % 12;
} // loop()


void dht11()
{
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //ReadTemperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    lcd.println("Failed to read from DHT sensor!");
    return;
  }
    lcd.print("T=");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("H=");
    lcd.print(h);
    lcd.print("%");
    delay(2000) ;
    if (h>=th)
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
}

void mq3()
{
  gas_read = analogRead(MQ3_PIN);
  delay(1000);
  lcd.print("MQ3=");
  lcd.print(gas_read);
  delay(2000);
  if (gas_read>=th1)
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
}

void ldr()
{ 
  delay(1000);
  ldr_read = analogRead(LDR_PIN);
  lcd.print("LDR=");
  lcd.print(ldr_read);
 //lcd.print("\n");
}

void sendSms()
{
    if(readData()){
      int f=0;
      String dataMessage;
      if(h>th)
        f=1;
      delay(10);
      // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
      // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
      SIM900.println("AT + CMGS = \"+919606703680\"");
      delay(100);
      
      // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
      if(f)
       dataMessage = ("Temperature: " + String(t) + "*C " + "\n" + " Humidity: " + String(h) + "%" + "\n" + "MQ3 :" + String(mq) + "\n" + "LDR :" + String(ldr1) + "\n" + "Food Spoilt.");
      else
       dataMessage = ("Temperature: " + String(t) + "*C " + "\n" + " Humidity: " + String(h) + "%" + "\n" + "MQ3 :" + String(mq) + "\n" + "LDR :" + String(ldr1) + "\n" +"Food OK.");
      
      
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
    }
  
  delay(10); 
}

boolean readData()
{
  //Read humidity
  h = dht.readHumidity();
  // Read temperature as Celsius
  t = dht.readTemperature();
  // Read temperature as Fahrenheit
  f = dht.readTemperature(true);

  mq = analogRead(MQ3_PIN);

  ldr1= analogRead(LDR_PIN);
 
  // Compute temperature values in Celcius
  t = dht.computeHeatIndex(t,h,false);

  // Uncomment to compute temperature values in Fahrenheit
  //f = dht.computeHeatIndex(f,h,false);

  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }
  
//  Serial.print("Humidity: "); 
//  Serial.print(h);
//  Serial.print(" %\t");
//  Serial.print("Temperature: "); 
//  Serial.print(t);
//  Serial.print(" *C ");
  
  //Uncomment to print temperature in Farenheit
  //Serial.print(f);
  //Serial.print(" *F\t");
  delay(10000);  //check every 10s
  if((h>th)&&(mq>th1))
    return true;
   else
    return false;
  delay(1000);
  gas_read = analogRead(MQ3_PIN);
  ldr_read = analogRead(LDR_PIN);
// lcd.print(gas_read); 
}
