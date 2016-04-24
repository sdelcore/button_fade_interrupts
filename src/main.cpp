#include <Arduino.h>

//When the button is pressed the led will cycle through brightness and stop when it's 0
//Assign pins and values to corresponding variables
const int ledPIN = 9;
const int pushButton = 2;

int brightness = 0;
int fadeAmount = 5;

volatile int buttonState = 0;

void button_ISR();
void fade_LED();

void setup() {
  Serial.begin(9600); //Allow the Arduino to write to the log console
  pinMode(ledPIN, OUTPUT);
  pinMode(pushButton, INPUT); //Assign input and output pins
  attachInterrupt(0, button_ISR, FALLING); //attaches an inerrupt to the ISR vector 0 is for pin 1 and 2
}

void loop() {
  if (buttonState) {
    fade_LED();
  }
}

void button_ISR() {
  buttonState = 1;
}

void fade_LED() {
  Serial.write(buttonState);
  buttonState = 0;
  bool Done = false;
  while (!Done)
  {
    brightness = brightness + fadeAmount;
    analogWrite(ledPIN,brightness);
    Serial.write(brightness);
    delay(100);

    if (brightness >= 255 ) {
      fadeAmount = -fadeAmount;
    }

    if ( brightness <= 0 ) {
      Done = true;
      brightness = 0;
      analogWrite(ledPIN,brightness);
      fadeAmount = -fadeAmount;
    }
  }
}
