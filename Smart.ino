#define BLYNK_TEMPLATE_ID           "Your Template ID"
#define BLYNK_TEMPLATE_NAME         "Template name"
#define BLYNK_AUTH_TOKEN            "Your auth token"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>                                 // temperature sensor 
#include <DallasTemperature.h>                 // temperature sensor
#include <Servo.h>                                      // servo for feeder

char ssid[] = "Your WiFi name";              // ssid of WiFi to be connected
char pass[] = "Your WiFi password";                            // password of WiFi
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
Servo s1;

void sendSensor()                                          // reads sensor value
{
  // Request temperature to all devices on the data line
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  //We can connect more than one IC on the same data wire. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  int tempC=sensors.getTempCByIndex(0);
  int tempF=sensors.getTempFByIndex(0);
  delay(1000);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V5, tempC);
    Blynk.virtualWrite(V6, tempF);
    delay(500);
}

int pos=0;
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V0 to a variable
  if (pinValue==0){
    digitalWrite(D1,HIGH);
  }
  else{
    digitalWrite(D1,LOW);
  }
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (pinValue==0){
    digitalWrite(D2,HIGH);
  }
  else{
    digitalWrite(D2,LOW);
  }
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  if (pinValue==0){
    digitalWrite(D3,HIGH);
  }
  else{
    digitalWrite(D3,LOW);
  }
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  if (pinValue==1){
      s1.write(30);
      delay(500);
      s1.write(0);
      delay(500);
  }
}
void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);

  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  s1.attach(15);
  sensors.begin();
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{ 
  Blynk.run();
  sendSensor();
}
