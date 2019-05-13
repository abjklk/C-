//esp8266
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

String apiKey = "WHDAH0QDAX87U2PA";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "DLink";           // replace with your wifi ssid and wpa2 key
const char *pass =  "gaurav123";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  // Initialize Serial port
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
      
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  Serial.println("hi");
  if (root == JsonObject::invalid())
  {
    Serial.println("invalid");  
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int temp=root["temp"];
  Serial.println(temp);
  Serial.print("Humidity ");
  int humid=root["hum"];
  Serial.println(humid);
  Serial.print("gas sensor ");
  int gas=root["gasv"];
  Serial.println(gas);
  Serial.print("ldr ");
  int ldr=root["ldr"];
  Serial.println(ldr);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
  Serial.println("Uploading...");

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temp);
    postStr +="&field2=";
    postStr += String(humid);
    postStr +="&field3=";
    postStr += String(gas);
    postStr +="&field4=";
    postStr += String(ldr);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
//    Serial.print("Temperature: ");
//    Serial.print(t);
//    Serial.print(" degrees Celcius, Humidity: ");
//    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");                        
   }
    client.stop();
    Serial.println("Waiting...");
    // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
    delay(15000);
}
