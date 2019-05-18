 

/*

  Description: Simpel LED game
  Author: Frank Li
  Date: May, 18, 2019

 
*/

#include "pitches.h"

int buzzerPin = 6;    // Using digital pin 6

int counter = 0;

int currentLED = 2;

int delayValue = 180;

int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

int noteDurations[] = { 4, 8, 8, 4,4,4,4,4 };

byte seven_seg_digits[10][4] = {
                               {0,0,0,0}, //0
                               {0,0,0,1}, //1
                               {0,0,1,0}, //2
                               {0,0,1,1}, //3
                               {0,1,0,0}, //4
                               {0,1,0,1}, //5
                               {0,1,1,0}, //6
                               {0,1,1,1}, //7
                               {1,0,0,0}, //8
                               {1,0,0,1} //9
                               };

void setup() {

  // initialize digital pin 7 as input;

  pinMode(7, INPUT);   // button input
  
  // initialize digital pin 2 to 6, 8 to 11 as output:

  pinMode(2, OUTPUT);   // white LED
  pinMode(3, OUTPUT);   // yellow LED
  pinMode(4, OUTPUT);   // green LED
  pinMode(5, OUTPUT);   // red LED
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);   //8-10 Seven segment binary outputs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

int checkInput() { 

  if (digitalRead(7) == 0) {

     return 1;

  } else {

    return 0;

  }

  sevenSegWrite(counter);
}

 
void loop(){

  // Check if the button is pressed at the right moment

  if (digitalRead(7) == 0) {

     if (currentLED == 4) {

       // Blink the correct (green) LED
       tone(buzzerPin, NOTE_A4, 500);
       blinkit(4);

       counter++;
       sevenSegWrite(counter);

// Speed up the LEDs
       delayValue = delayValue - 20; 

//Check is user has won
       if(delayValue == 0){
        for(int thisNote = 0; thisNote < 8; thisNote++){
          
          int noteDuration = 1000/noteDurations[thisNote];
          tone(6,melody[thisNote],noteDuration);
          delay(noteDuration * 1.30);
        }
        
       }
 
    } else {

       // Blink the wrong LED
       tone(buzzerPin, NOTE_B0, 500);
       blinkit(currentLED);

    }

  }

  // Loop LED from white –> yellow –> green –> red

  digitalWrite(currentLED, HIGH);
  delay(delayValue);
  digitalWrite(currentLED, LOW);
  delay(delayValue);

  currentLED = currentLED + 1;

  if (currentLED > 5) {

     currentLED = 2;

  }

}

//Blink when LED has been pressed
void blinkit(int LED){
       digitalWrite(LED, HIGH);
       delay(200);
       digitalWrite(LED, LOW);
       delay(200);
       digitalWrite(LED, HIGH);
       delay(200);
       digitalWrite(LED, LOW);
       delay(200);
}


//Uses digital pin 8-11 to send binary inputs to CD4511 IC
void sevenSegWrite(byte digit) {

  byte pin = 8;
  for (byte binary = 0; binary < 4; binary++) {
    digitalWrite(pin, seven_seg_digits[digit][binary]);
    ++pin;
  }
}
