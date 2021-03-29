// Program used to test the Nintento Switch Joystick object on the
// Arduino Leonardo or Arduino Micro.
//
// Michele Perla for Hackerloop
// Edited by Jorand Le Pape
//------------------------------------------------------------
//
// Connect 12 buttons with pullups to pins A0 to A3 and to pins 0 to 7;
// When the button on A0 is pressed, buttons on pins 0-7 control Y,B,A,X,L,R,Zl,Zr;
// When the button on A1 is pressed, buttons on pins 0-5 control +,-,Lstick,Rstick,Home,Capture;
// When the button on A2 is pressed, buttons on pins 0-1 control Left Stick X axis, buttons on pins 2-3 control Left Stick Y axis,
//                                   buttons on pins 4-5 control Right Stick X axis, buttons on pins 4-5 control Right Stick Y axis
// When the button on A3 is pressed, buttons on pins 0-7 control the Hat Switch

#include "SwitchJoystick.h"

// Create Joystick
SwitchJoystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;

uint32_t timer = 0;

void setup() {

  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  //pinMode(0, INPUT_PULLUP); TX0
  //pinMode(1, INPUT_PULLUP); RX1
  //pinMode(2, INPUT_PULLUP); SDA
  //pinMode(3, INPUT_PULLUP); SCL
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  //pinMode(8, INPUT_PULLUP); Wierd
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);

  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();
}

void loop() {
  if (millis() > timer) {
    timer = millis() + 10; // 10 ms = 1/0.010 == 100Hz

    if (!digitalRead(A0)) {
      if (!digitalRead(4)){
        Joystick.pressButton(0); // Y
      } else {
        Joystick.releaseButton(0); // Y
      }
      if (!digitalRead(5)){
        Joystick.pressButton(1); // B
      } else {
        Joystick.releaseButton(1); // B
      }
      if (!digitalRead(6)){
        Joystick.pressButton(2); // A
      } else {
        Joystick.releaseButton(2); // A
      }
      if (!digitalRead(7)){
        Joystick.pressButton(3); // Z
      } else {
        Joystick.releaseButton(3); // Z
      }
      if (!digitalRead(9)){
        Joystick.pressButton(4); // L
      } else {
        Joystick.releaseButton(4); // L
      }
      if (!digitalRead(10)){
        Joystick.pressButton(5); // R
      } else {
        Joystick.releaseButton(5); // R
      }
      if (!digitalRead(16)){
        Joystick.pressButton(6); // Zl
      } else {
        Joystick.releaseButton(6); // Zl
      }
      if (!digitalRead(14)){
        Joystick.pressButton(7); // Zr
      } else {
        Joystick.releaseButton(7); // Zr
      }
    }
    else if (!digitalRead(A1)) {
      if (!digitalRead(4)){
        Joystick.pressButton(8); // -
      } else {
        Joystick.releaseButton(8); // -
      }
      if (!digitalRead(5)){
        Joystick.pressButton(9); // +
      } else {
        Joystick.releaseButton(9); // +
      }
      if (!digitalRead(6)){
        Joystick.pressButton(10); // Lstick
      } else {
        Joystick.releaseButton(10); // Lstick
      }
      if (!digitalRead(7)){
        Joystick.pressButton(11); // Rstick
      } else {
        Joystick.releaseButton(11); // Rstick
      }
      if (!digitalRead(9)){
        Joystick.pressButton(12); // Home
      } else {
        Joystick.releaseButton(12); // Home
      }
      if (!digitalRead(10)){
        Joystick.pressButton(13); // capture
      } else {
        Joystick.releaseButton(13); // capture
      }
    }
    else if (!digitalRead(A2)) {
      if (!digitalRead(4)){
        Joystick.setXAxis(255); // Left joystick RIGHT
      }
      else if (!digitalRead(5)){
        Joystick.setXAxis(0);   // Left joystick LEFT
      }
      else {
        Joystick.setXAxis(128); // Release
      }

      if (!digitalRead(6)){
        Joystick.setYAxis(255); // Left joystick DOWN
      }
      else if (!digitalRead(7)){
        Joystick.setYAxis(0);   // Left joystick UP
      }
      else {
        Joystick.setYAxis(128); // Release
      }

      if (!digitalRead(9)){
        Joystick.setZAxis(255); // Right joystick RIGHT (camera left)
      }
      else if (!digitalRead(10)){
        Joystick.setZAxis(0);   // Right joystick LEFT (camera right)
      }
      else {
        Joystick.setZAxis(128);// Release
      }

      if (!digitalRead(16)){
        Joystick.setRzAxis(255); // Right joystick DOWN (camera zoom out)
      }
      else if (!digitalRead(14)){
        Joystick.setRzAxis(0);  // Right joystick UP (camera zoom in)
      }
      else {
        Joystick.setRzAxis(128); // Release
      }
    }
    else if (!digitalRead(A3)) {
      if (!digitalRead(4)){
        Joystick.setHatSwitch(0); // UP
      }
      if (!digitalRead(5)){
        Joystick.setHatSwitch(90); // RIGHT
      }
      if (!digitalRead(6)){
        Joystick.setHatSwitch(180); // DOWN
      }
      if (!digitalRead(7)){
        Joystick.setHatSwitch(270); // LEFT
      }

      if (digitalRead(4) && digitalRead(5) && digitalRead(6) && digitalRead(7)) {
        Joystick.setHatSwitch(-1); // RELEASE
      }
    }

    Joystick.sendState();
  }
}