#include "Keyboard.h"

#define panelPins 22
int pinStatus[panelPins];
int curentPin;
int newStatus;
char shortcuts[panelPins];

// https://en.wikipedia.org/wiki/ASCII - DEC chars, 0 is skip value
//128, 130, 65
int keyboardCommands[22][3] = {
  {130, 66, 0}, //0 pin ALT+B BAT
  {129, 130, 71}, //1 pin SHIFT+ALT+G
  {130, 65, 0}, //2 pin ALT+A ALT
  {128, 130, 65}, //3 pin 
  {130, 80, 0}, //4 pin ALT+P PUMP
  {129, 72, 0}, //5 pin ALT+H PT-HEAD
  {0, 72, 0}, //6 pin H DEICE
  {0, 0, 0}, //7 pin 
  {0, 201, 0}, //8 pin 
  {0, 0, 0}, //9 pin GEARS CONROL SKIPED, SEARCH IN MAIN 
  {0, 0, 0}, //10 pin 
  {0, 0, 0}, //11 pin 
  {0, 0, 0}, //12 pin 
  {0, 0, 0}, //13 pin 
  {128, 76, 0}, //14 pin CTRL+L LANDING
  {130, 74, 0}, //15 pin TAXI
  {0, 0, 0}, //16 pin
  {0, 0, 0}, //17 pin
  {0, 79, 0}, //18 pin O STROBE
  {130, 78, 0}, //19 pin ALT+N NAV
  {130, 72, 0}, //20 pin ALT+H BEACON
  {0, 0, 0}, //21 pin 
};

void setup() {

  for (int i = 0; i < panelPins; i++){
    pinMode(i, INPUT_PULLUP);
    digitalWrite(i, 1);
    pinStatus[i] = 1;
  }

  // KEYBOARD LIB INIT AND WAIT
  Keyboard.begin(); 
  delay(200); 

  Serial.println("Setup end");
}

void loop() {

  for(int y = 0; y < panelPins; y++){
    newStatus = digitalRead(y);
    if(newStatus != pinStatus[y]){
      pinStatus[y] = newStatus;
      for(int x = 0; x < 3; x++){
        if(keyboardCommands[y][x] != 0){
          Keyboard.press(keyboardCommands[y][x]);
        }
      }
      
      // FLAPS CONTROLL
      if(y == 10 && digitalRead(y) == 0){
        Keyboard.press(198);
      }else if(y == 10 && digitalRead(y) == 1){
        Keyboard.press(198);
        Keyboard.press(200);
      }

      // GEARS CONTROLL
      if(y == 9){
        // CTRL + SHIFT + ALT + E ####### U MUST SET IT MANUALY IN GAME SETTINGS
        Keyboard.press(128); 
        Keyboard.press(129);
        Keyboard.press(130);
        Keyboard.press('E');
      }

//      
//      if(y == 3 && digitalRead(y) == 0){// CTRL+ALT+A AVIONICS ####### U MUST SET IT MANUALY IN GAME SETTINGS
//        Keyboard.press(128); 
//        Keyboard.press(129);
//        Keyboard.press(130);
//        Keyboard.press('A');
//      }else if(y == 3 && digitalRead(y) == 1){// CTRL+ALT+A AVIONICS ####### U MUST SET IT MANUALY IN GAME SETTINGS
//        Keyboard.press(128);
//        Keyboard.press(130);
//        Keyboard.press('A');
//      }
      
      delay(200);
      Keyboard.releaseAll();
      
       // UNCOMMENT FOR DEBUG
       Serial.print(y);Serial.print(" ");Serial.println(newStatus);
      delay(50);
    }
  }
}
