// libraries
#include <RGBLed.h>
#include <HCSR04.h>
#include <LiquidCrystal.h>


// define pins
RGBLed led(2, 3, 4, RGBLed::COMMON_CATHODE);
HCSR04 hc(5, 6);  // trig, echo
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int hazardPin = 13;


void stop();
void amber();
void go();
void motionDetect(char message[], bool ticket);
void lcdDisplay(char message[]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(hazardPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  stop();
  go();
  amber();
}

void stop() {
  led.brightness(RGBLed::RED, 80);
  lcdDisplay("STOP");
  motionDetect("VIOLATION", true);
}
void go() {
  led.brightness(RGBLed::GREEN, 50);
  lcdDisplay("GO");
  motionDetect("Go Ahead", false);
}
void amber() {
  led.brightness(253, 140, 0, 60);
  lcdDisplay("CAUTION");
  motionDetect("Careful.", false);
}


void motionDetect(char message[], bool ticket) {
  unsigned long start = millis();
  while ((millis() - start) < 5000) { // current time - start time
    
  lcd.setCursor(0, 1);
  lcd.print( 5 - ( (millis() - start) / 1000 ) );

    if (hc.dist() < 5) {
      Serial.println(message);
      if (ticket) {digitalWrite(hazardPin, HIGH);}
      delay(60);
    }
    else {
      digitalWrite(hazardPin, LOW);
    }
  }
}

void lcdDisplay(char message[])
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

