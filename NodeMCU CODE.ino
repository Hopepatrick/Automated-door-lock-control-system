#define BLYNK_TEMPLATE_ID "TMPL43dyx9N2"
#define BLYNK_TEMPLATE_NAME "FIRST"
#define BLYNK_AUTH_TOKEN "g_jU2bzID1jvAwuQofGRQBnqIXTRTxfQ"
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
BlynkTimer timer;
String incomming;
char auth[] = BLYNK_AUTH_TOKEN;  //Enter your Blynk Auth token
char ssid[] = "Immobilizer";  //Enter your WIFI SSID
char pass[] = "123456789";  //Enter your WIFI Password
int buttonState;
void setup() {
  pinMode(D3,INPUT_PULLUP);
  pinMode(D2,OUTPUT);
 Serial.begin(9600);
Serial.setTimeout(10);
digitalWrite(D2,LOW);
  Blynk.begin(auth, ssid, pass);
 
timer.setInterval(1000L,notification); 
//timer.setInterval(100L,detect);
}
void notification(){
if(Serial.available()>0){
    incomming = Serial.readString();
    Serial.println(incomming);
    Blynk.virtualWrite(V3, incomming);
  }
}

BLYNK_WRITE(V1){
  buttonState = param.asInt(); // Check virtual status from blynk iot
}


void loop() {
  if(digitalRead(D3)==0){
    Serial.println(digitalRead(D3)); // This is to check if door is locked or unlocked
    Blynk.virtualWrite(V2, "Unlocked"); 
  }
  else{
    Blynk.virtualWrite(V2, "Locked");
  }
  if(buttonState==1){
    digitalWrite(D2,HIGH);
  }
  else{
    digitalWrite(D2,LOW);
  }
  
Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
