/*
 * Project IoT_Lab8
 * Description:
 * Author:
 * Date:
 */

#include "oled-wing-adafruit.h"
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"


SYSTEM_MODE(MANUAL);
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
      digitalWrite(GREEN_LIGHT, HIGH);
    }else if (ambient < 2400){
      digitalWrite(YELLOW_LIGHT, HIGH);
    }else{
      digitalWrite(RED_LIGHT, HIGH);
    }
    }
  }

  display.setCursor(0,0);
  display.display();
}