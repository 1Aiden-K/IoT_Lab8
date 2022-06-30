/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab8/src/IoT_Lab8.ino"
/*
 * Project IoT_Lab8
 * Description:
 * Author:
 * Date:
 */

#include "oled-wing-adafruit.h"
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include <blynk.h>

void setup();
void loop();
#line 13 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab8/src/IoT_Lab8.ino"
SYSTEM_THREAD(ENABLED);

bool oledVeiw = true;
bool oledOn = true;

VCNL4040 proximitySensor;
OledWingAdafruit display;

#define RED_LIGHT D8
#define YELLOW_LIGHT D7
#define GREEN_LIGHT D6

void setup() {
  Wire.begin();

  Blynk.begin("h9VMR0qLvSa2MKcs1Xy7SXPzGGI8xFhZ", IPAddress(167, 172, 234, 162), 8080);

  proximitySensor.begin();
  proximitySensor.powerOnProximity();
  proximitySensor.powerOnAmbient();

  pinMode(RED_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);

  display.setup();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);

}

void loop() {
  display.loop();
  Blynk.run();
  display.clearDisplay();
  unsigned int proximity = proximitySensor.getProximity(); 
  unsigned int ambient = proximitySensor.getAmbient(); 

  digitalWrite(RED_LIGHT,LOW);
  digitalWrite(YELLOW_LIGHT,LOW);
  digitalWrite(GREEN_LIGHT,LOW);

  if (display.pressedA()){
    oledVeiw = true;
    oledOn = true;
  }else if (display.pressedB()){
    oledVeiw  = false;
    oledOn = true;
  }else if (display.pressedC()){
    if(oledOn){
      oledOn = false;
    }else{
      oledOn = true;
    }
  }

  if (oledOn){
    if(oledVeiw){
      display.println("Proximity Level:");
      display.println(proximity);

    if (proximity < 25){
      digitalWrite(GREEN_LIGHT, HIGH);
    }else if (proximity < 250){
      digitalWrite(YELLOW_LIGHT, HIGH);
    }else{
      digitalWrite(RED_LIGHT, HIGH);
    }
    }else{
      display.println("Ambeint Light Level:");
      display.println(ambient);

    if (ambient < 1000){
      digitalWrite(RED_LIGHT, HIGH);
    }else if (ambient < 2400){
      digitalWrite(YELLOW_LIGHT, HIGH);
    }else{
      digitalWrite(GREEN_LIGHT, HIGH);
    }
    }
  }else{
    Blynk.virtualWrite(V0, proximity);
    Blynk.virtualWrite(V1, ambient);
  }

  display.setCursor(0,0);
  display.display();
}