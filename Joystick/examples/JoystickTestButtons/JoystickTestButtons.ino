// Program used to test the USB Joystick object on the 
// Arduino Leonardo or Arduino Micro.
//
// Matthew Heironimus
// 2015-03-28 - Original Version
// 2015-11-18 - Updated to use the new Joystick library 
//              written for Arduino IDE Version 1.6.6 and
//              above.
// 2016-05-13   Updated to use new dynamic Joystick library
//              that can be customized.
//------------------------------------------------------------

#include "Joystick.h"

// Create Joystick
Joystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;

void setup() {
  
  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();
}

void loop() {
  if(!digitalRead(A0)){
    if (!digitalRead(0)){
      Joystick.pressButton(0); // Y
    }else if (!digitalRead(1)){
      Joystick.pressButton(1); // B
    }else if (!digitalRead(2)){
      Joystick.pressButton(2); // A
    }else if (!digitalRead(3)){
      Joystick.pressButton(3); // Z
    }else if (!digitalRead(4)){
      Joystick.pressButton(4); // L
    }else if (!digitalRead(5)){
      Joystick.pressButton(5); // R
    }else if (!digitalRead(6)){
      Joystick.pressButton(6); // Zl
    }else if (!digitalRead(7)){
      Joystick.pressButton(7); // Zr
    }else{
      Joystick.releaseButton(0);
      Joystick.releaseButton(1);
      Joystick.releaseButton(2);
      Joystick.releaseButton(3);
      Joystick.releaseButton(4);
      Joystick.releaseButton(5);
      Joystick.releaseButton(6);
      Joystick.releaseButton(7);
      Joystick.releaseButton(8);
    }
  }
  else if(!digitalRead(A1)){
  if (!digitalRead(0)){
      Joystick.pressButton(8); // -
    }else if (!digitalRead(1)){
      Joystick.pressButton(9); // +
    }else if (!digitalRead(2)){
      Joystick.pressButton(10); // Lstick
    }else if (!digitalRead(3)){
      Joystick.pressButton(11); // Rstick
    }else if (!digitalRead(4)){
      Joystick.pressButton(12); // Home
    }else if (!digitalRead(5)){
      Joystick.pressButton(13); // capture
    }else if (!digitalRead(6)){
      Joystick.pressButton(14);
    }else if (!digitalRead(7)){
      Joystick.pressButton(15);
    }else{
      Joystick.releaseButton(8);
      Joystick.releaseButton(9);
      Joystick.releaseButton(10);
      Joystick.releaseButton(11);
      Joystick.releaseButton(12);
      Joystick.releaseButton(13);
      Joystick.releaseButton(14);
      Joystick.releaseButton(15);
    }
  }else if(!digitalRead(A2)){
  if (!digitalRead(0)){
      Joystick.setXAxis(255); // Left joystick RIGHT
    }else if (!digitalRead(1)){
      Joystick.setXAxis(0);   // Left joystick LEFT
    }else if (!digitalRead(2)){
      Joystick.setYAxis(255); // Left joystick DOWN
    }else if (!digitalRead(3)){
      Joystick.setYAxis(0);   // Left joystick UP
    }else if (!digitalRead(4)){
      Joystick.setZAxis(255); // Right joystick RIGHT (camera left)
    }else if (!digitalRead(5)){
      Joystick.setZAxis(0);   // Right joystick LEFT (camera right)
    }else if (!digitalRead(6)){
      Joystick.setRzAxis(255); // Right joystick DOWN (camera zoom out)
    }else if (!digitalRead(7)){
      Joystick.setRzAxis(0);  // Right joystick DOWN (camera zoom in)
    }else{
      Joystick.setXAxis(128);
      Joystick.setYAxis(128);
      Joystick.setZAxis(128);
      Joystick.setRzAxis(128);
    }
  }
  else if(!digitalRead(A3)){
  if (!digitalRead(0)){
      Joystick.setHatSwitch(0); // UP
    }else if (!digitalRead(1)){
      Joystick.setHatSwitch(45); // UP
    }else if (!digitalRead(2)){
      Joystick.setHatSwitch(90); // RIGHT
    }else if (!digitalRead(3)){
      Joystick.setHatSwitch(135); // DOWN
    }else if (!digitalRead(4)){
      Joystick.setHatSwitch(180); // DOWN
    }else if (!digitalRead(5)){
      Joystick.setHatSwitch(225); // DOWN
    }else if (!digitalRead(6)){
      Joystick.setHatSwitch(270); // LEFT
    }else if (!digitalRead(7)){
      Joystick.setHatSwitch(315); // UP
    }else{
      Joystick.setHatSwitch(-1);
    }
  }
  Joystick.sendState();
  delay(50);
}
