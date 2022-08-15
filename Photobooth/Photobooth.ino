
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
int pirPin = 6; //digital 6
int intMotion = 0;       // initialize motion to zero
int intNoMotion = 0;   

int greenLED=11;     // initialize pin to 11 
int blueLED=10;     // initialize pin to 10
int redLED=13;     // intialize pin to 13

boolean buttonselect;

void setup(){
Serial.begin(9600);
pinMode(pirPin, INPUT);
lcd.begin(16, 2);
int time = millis();
time = millis() - time;

pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);
pinMode(redLED, OUTPUT);
pinMode(shutterPin, OUTPUT);

digitalWrite(shutterPin, HIGH); // TEST pass!
}


void loop(){
uint8_t buttons = lcd.readButtons();
int pirVal = digitalRead(pirPin);

if(pirVal == LOW){                 //was motion detected
Serial.println("Motion Detected");
delay(1000);
intMotion = intMotion+1;
if(intMotion>3){
lcd.setBacklight(VIOLET);
lcd.setCursor(0, 0);
lcd.print ("Photobooth");
lcd.setCursor (0,1);
lcd.print ("Take a photo");
delay(2000);                   // 2 second delay
lcd.setCursor(0,0);
lcd.print("Select for Pic");
lcd.setCursor(0,1);
lcd.print("UP for Jump");
delay(3000);                  // 3 second delay
lcd.clear();
lcd.setCursor(0,0);
lcd.print("LEFT: 2 RIGHT: 4");  // the 4 is currently displaying over all over the following iterations.
lcd.setCursor(0,1);
lcd.clear();
lcd.print("DOWN: 3 PICS");
delay(1000);                    // 1 second delay
lcd.clear();
lcd.setCursor(0,0);
}
}

if (buttons) {                     // goal is: "if" sensor "then photo" 
lcd.clear();
lcd.setCursor(0,0);
//SELECT BUTTON --> TAKES 1 PHOTO
if (buttons & BUTTON_SELECT) {
intMotion = 0;

lcd.clear();
lcd.print("Taking a photo");
lcd.setBacklight(YELLOW);
delay(1000);
lcd.clear();

RGBtest();

digitalWrite(shutterPin, HIGH);   // trip the shutter -- transition on relay (square wave on oscilloscope?)
delay(500);
digitalWrite(shutterPin, LOW); // trip the shutter
delay(500);
}

//UP BUTTON --> TAKES JUMP SHOTS -- 3 CONSECUTIVE SHOTS
if (buttons & BUTTON_UP) {
intMotion = 0;
RGBjump();
}

//LEFT BUTTON --> 2 photos
if (buttons & BUTTON_LEFT) {
intMotion = 0;

lcd.clear();
lcd.print("Taking 2 photos");
lcd.setBacklight(YELLOW);
delay(1000);
lcd.clear();

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);
lcd.clear();

RGBtest();
digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);
}

//DOWN BUTTON --> 3 photos
if (buttons & BUTTON_DOWN) {
intMotion = 0;

lcd.clear();
lcd.print("Taking 3 photos");
lcd.setBacklight(YELLOW);
delay(1000);
lcd.clear();

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);
}

//BUTTON RIGHT --> TAKES 4 PHOTOS
if (buttons & BUTTON_RIGHT) {
intMotion = 0;

lcd.clear();
lcd.print("Taking 4 photos");
lcd.setBacklight(YELLOW);
delay(1000);
lcd.clear();

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);

RGBtest();

digitalWrite(shutterPin, HIGH);
delay(500);
digitalWrite(shutterPin, LOW);
delay(500);
}
}

else if (pirVal == HIGH) {
Serial.println("No Motion Detected");
delay(1000);
intMotion = 0;
intNoMotion = intNoMotion+1;
if(intNoMotion>3){
lcd.setBacklight(WHITE);
lcd.clear();}
}
}




void RGBtest()
{ //Low is on the color that lights bc we're dealing with a common anode--so things are backwards
//RED light
lcd.clear();
digitalWrite(redLED, LOW);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, HIGH);
lcd.setBacklight(RED);
lcd.setCursor (3,0);
lcd.print ("3");
delay(1000);
lcd.clear();

//BLUE light
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, LOW);
digitalWrite(greenLED, HIGH);
lcd.setBacklight(GREEN);
lcd.setCursor (3,0);
lcd.print ("2");
delay(1000);
lcd.clear();

//GREEN light
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, LOW);
lcd.setBacklight(BLUE);
lcd.setCursor (3,0);
lcd.print ("1");
delay(1000);
lcd.clear();

//SMILE!
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, HIGH);
lcd.clear();
lcd.setBacklight(VIOLET);
lcd.print("SMILE!");
return; }


void RGBjump()
{
//Low is on the color that lights bc we're dealing with a common anode (so things are backwards)
lcd.clear();
lcd.print("Jump after one");
lcd.setBacklight(YELLOW);
delay(1000);
lcd.clear();

//RED light
digitalWrite(redLED, LOW);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, HIGH);
lcd.setBacklight(RED);
lcd.setCursor (3,0);
lcd.print ("3");
delay(1000);
lcd.clear();

//BLUE light
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, LOW);
digitalWrite(greenLED, HIGH);
lcd.setBacklight(GREEN);
lcd.setCursor (3,0);
lcd.print ("2");
delay(1000);
lcd.clear();

//GREEN light
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, LOW);
lcd.setBacklight(BLUE);
lcd.setCursor (3,0);
lcd.print ("1");
delay(1000);
lcd.clear();

//Smile!
digitalWrite(redLED, HIGH);
digitalWrite(blueLED, HIGH);
digitalWrite(greenLED, HIGH);
lcd.clear();
lcd.setBacklight(VIOLET);
lcd.print("JUMP!!!!");

digitalWrite(shutterPin, HIGH);
delay(300);
digitalWrite(shutterPin, LOW);
delay(25);

digitalWrite(shutterPin, HIGH);
delay(300);
digitalWrite(shutterPin, LOW);
delay(25);

digitalWrite(shutterPin, HIGH);
delay(400);
digitalWrite(shutterPin, LOW);
delay(50);

return;
}




