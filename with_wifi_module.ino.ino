/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's rather tricky to get it working, please read this article:
    https://github.com/blynkkk/blynk-library/wiki/ESP8266-with-AT-firmware

  Simple e-mail example

  App project setup:
    E-mail Widget

  Connect a button to digital pin 2 and GND
  Pressing this button will send an e-mail

  WARNING: You are limited to send ONLY ONE E-MAIL PER 15 SECONDS!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/* Set this to a bigger number, to enable sending longer messages */
//#define BLYNK_MAX_SENDBYTES 128

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
const int trig = 12;
const int echo = 11;
const int leftForward = 6;
const int leftBackward = 7;
const int rightForward = 4;
const int rightBackward = 5;
const int buzzer = 10;

int duration = 0;
int distance = 0;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "60072c16c7b5451abdca5e4e2bd66103";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hmcs";
char pass[] = "sonia123";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void emailOnButtonPress()
{
  // *** WARNING: You are limited to send ONLY ONE E-MAIL PER 15 SECONDS! ***

  // Let's send an e-mail when you press the button
  // connected to digital pin 2 on your Arduino

 if(distance>5)
{
  Serial.println(distance);
Serial.print("mail sent to device");
 Blynk.email("dilleswarraomandala@gmail.com","Alert message","The person is at danger"); 
}
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
   pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
pinMode(buzzer, OUTPUT);

 Serial.begin(9600);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Send e-mail when your hardware gets connected to Blynk Server
  // Just put the recepient's "e-mail address", "Subject" and the "message body"
  Blynk.email("your_email@mail.com", "Subject", "My Blynk project is online.");

  // Setting the button
  pinMode(2, INPUT_PULLUP);
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(echo), emailOnButtonPress, CHANGE);
}

void loop()
{
  Blynk.run();
    digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
   if ( distance > 20 )
  {
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , HIGH);//if the obstacle is greater than 20--moving forward
    digitalWrite(rightForward , HIGH);
    digitalWrite(rightBackward , LOW);
 digitalWrite(buzzer, LOW);
 
    delay(100);
  }
 else if( distance >10 ) 
 {
  digitalWrite(leftForward , HIGH);
    digitalWrite(leftBackward , LOW);
    digitalWrite(rightForward , HIGH);// if obstacle is greater than 10 and lessthan 20--moving left
    digitalWrite(rightBackward , LOW);
 digitalWrite(buzzer, HIGH);
  

 }
 else if(distance<5)
{
  Serial.println(distance);
Serial.print("mail sent to device");
 Blynk.email("dilleswarraomandala@gmail.com","Alert message","The person is at danger"); 
}
 else
  {
    digitalWrite(leftForward , LOW);
    digitalWrite(leftBackward , LOW);// if obstacle is less than 10--automatic braking stop
    digitalWrite(rightForward , LOW);
    digitalWrite(rightBackward , LOW);
        digitalWrite(buzzer, HIGH);
   
  }
}

