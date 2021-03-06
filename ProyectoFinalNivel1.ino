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
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <Stepper.h>
  
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "KLtiieKVE-fmogTN3OLKJCbsDW_uSHQH";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Josephus";
char pass[] = "123456789";

int PinServo1 = 2;
int PinServo2 = 4;
int PinServo3 = 5;

Servo Servo1;
Servo Servo2;
Servo Servo3;

const int stepsPerRevolution = 2038;
Stepper Stepper1 = Stepper(stepsPerRevolution,D5,D7,D6,D8);

int Direction=3;
void setup()
{
  // Debug console
   
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Servo1.attach(PinServo1);
  Servo1.write(90);
  Servo2.attach(PinServo2);
  Servo2.write(0);
  Servo3.attach(PinServo3);
  Servo3.write(90);
}

void loop()
{
  Blynk.run();
  if (Direction==0){
    yield();
    Stepper1.step(1);
    delayMicroseconds(3000);
  }else if(Direction==1){
    yield(); 
    Stepper1.step(-1);
    delayMicroseconds(3000);
  }
 
}

BLYNK_WRITE(V1){
  Servo1.write(map(2*param.asInt(), 0, 90, 90,0));
}
BLYNK_WRITE(V2){
  Servo2.write(map(2*param.asInt(),0,90,90,0));
}
BLYNK_WRITE(V3){
  if(param.asInt()==1){
  Servo3.write(0);
  }else{
  Servo3.write(180);
  }
}

BLYNK_WRITE(V4){
 if(param.asInt()==1){
  Direction= 0;
 }else{
  Direction = 3;
 }
}

BLYNK_WRITE(V5){
 if(param.asInt()==1){
  Direction= 1;
 }else{
  Direction = 3;
 }
}
