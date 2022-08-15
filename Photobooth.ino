// ----------------------------------------
// Photobooth Code (this is the one you'll actually be using)
// ----------------------------------------

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>


Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Set backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int shutterPin = 5; //digital 5 that connects to camera shutter
int pirPin = 6;      //digital 6 motion detector

int greenLED=11;     // initialize pin to 11 (test)
int blueLED=10;     // initialize pin to 10   (test)
int redLED=13;     // intialize pin to 13     (test)


void setup(){
      
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setBacklight(GREEN);
    
    pinMode(shutterPin, OUTPUT);
    digitalWrite(shutterPin, HIGH);

    pinMode(pirPin, INPUT);   // pins are assumed as input on the arduino
    
    
    pinMode(2,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(7,INPUT_PULLUP);
    pinMode(8,INPUT_PULLUP);
    pinMode(12,INPUT_PULLUP);


}
int f = 0;
void loop(){
    int pirVal = digitalRead(pirPin);
    Serial.println(pirVal);
    Serial.println(f);
    delay(100);
    f++;

    if(pirVal == HIGH){  //was motion detected       
        Serial.println("Motion Detected");
        printWithColorTimed("Strike a pose!", YELLOW, 1000);
        printWithColorTimed("Three", RED, 1000);
        printWithColorTimed("Two", YELLOW, 1000);
        printWithColorTimed("One", GREEN, 1000);
        printWithColorTimed("Smile!", WHITE, 1000);
        lcd.clear();
        lcd.setBacklight(WHITE);
  
        
        digitalWrite(shutterPin, HIGH);
        delay(1000);
        digitalWrite(shutterPin, LOW);
        delay(1000);

    }
    else if (pirVal == LOW) {
        Serial.println("No Motion Detected");
        printWithColorTimed("Waiting...", TEAL, 1000);
        digitalWrite(shutterPin, LOW);
        delay(1000);
    }
    
}

void printWithColorTimed(String str, int color, int delay_time){
  printWithColor(str, color);
  delay(delay_time);
}

void printWithColor(String str, int color){
  lcd.clear();
  lcd.setBacklight(color);
  lcd.setCursor(0,0);
  lcd.print(str);
}



