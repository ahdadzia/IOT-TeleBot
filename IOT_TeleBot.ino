#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "CTBot.h"
CTBot myBot;

String ssid = "Galaxy A50sB167";     
String pass = "mcks1999"; 
String token = "1236134269:AAFPhEjdkbyjRcfxjPaJSPQwD5wNs0Y_dME";   
uint8_t redLed = D1;               
uint8_t greenLed = D0;                       
                                    

void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");

  myBot.wifiConnect(ssid, pass);

  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, LOW); 
  digitalWrite(greenLed, LOW);

}

void loop() {
  TBMessage msg;

  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("Merah nyala")) {              
      digitalWrite(redLed, HIGH);                               
      myBot.sendMessage(msg.sender.id, "Red Light is now ON");  
    }
    else if (msg.text.equalsIgnoreCase("Merah mati")) {        
      digitalWrite(redLed, LOW);                              
      myBot.sendMessage(msg.sender.id, "Red Light is now OFF"); 
    }
      if (msg.text.equalsIgnoreCase("Hijau nyala")) {              
      digitalWrite(greenLed, HIGH);                               
      myBot.sendMessage(msg.sender.id, "Green Light is now ON");  
    }
    else if (msg.text.equalsIgnoreCase("Hijau mati")) {         
      digitalWrite(greenLed, LOW);                              
      myBot.sendMessage(msg.sender.id, "Green Light is now OFF"); 
    }
     if (msg.text.equalsIgnoreCase("Kedap kedip")) {        
      digitalWrite(redLed, HIGH);
      delay(100);
      digitalWrite(greenLed, HIGH);
      delay(100);
      digitalWrite(redLed, LOW);
      delay(100);
      digitalWrite(greenLed, LOW);
      delay(100);                              
      myBot.sendMessage(msg.sender.id, "Flip Flop");
     }
     
    else {                                                    
      
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
      myBot.sendMessage(msg.sender.id, reply);             
    }
  }
  
  delay(1);
}
