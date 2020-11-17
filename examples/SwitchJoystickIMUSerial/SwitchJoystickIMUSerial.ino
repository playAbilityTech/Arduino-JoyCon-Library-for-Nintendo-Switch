// Program used to test the Nintento Switch Joystick object on the
// Arduino Leonardo or Arduino Micro.
//
// Michele Perla for Hackerloop
//------------------------------------------------------------
//

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "SwitchJoystick.h"

// Create Joystick
SwitchJoystick_ Joystick;

MPU6050 mpu;

const int ADC_Max = 1023;  // 10 bit

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;

// MPU6050
#define SCALING 4        // max Joystick value  at 90deg/SCALING.

#define INTERRUPT_PIN 7  // use pin 2 on Arduino Uno & most boards

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float pitchOffset = 0;
float rollOffset = 0;

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() { mpuInterrupt = true; }

int leftJoyX = 128;
int leftJoyY = 128;

unsigned long onTime = 0;
unsigned long releaseTime = 0;

void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(50);

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

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  //pinMode(2, INPUT_PULLUP); SDA
  //pinMode(3, INPUT_PULLUP); SCL
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  //pinMode(7, INPUT_PULLUP); INT MPU
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

  // set up MPU6050
  Wire.begin();
  Wire.setClock(400000);
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    fail();
  }

}

bool buttonY = false;
bool buttonB = false;
bool buttonA = false;
bool buttonX = false;
bool buttonL = false;
bool buttonR = false;
bool buttonZl = false;
bool buttonZr = false;

bool buttonMinus = false;
bool buttonPlus = false;
bool buttonLstick = false;
bool buttonRstick = false;
bool buttonHome = false;
bool buttonCapture = false;

bool LeftJoyRIGHT = false;
bool LeftJoyLEFT = false;
bool LeftJoyDOWN = false;
bool LeftJoyUP = false;

bool RightJoyRIGHT = false;
bool RightJoyLEFT = false;
bool RightJoyDOWN = false;
bool RightJoyUP = false;

bool HatUP = false;
bool HatRIGHT = false;
bool HatDOWN = false;
bool HatLEFT = false;

void loop() {

  if ((millis() - releaseTime) > 50) {
    buttonY = false;
    buttonB = false;
    buttonA = false;
    buttonX = false;
    buttonL = false;
    buttonR = false;
    buttonZl = false;
    buttonZr = false;

    buttonMinus = false;
    buttonPlus = false;
    buttonLstick = false;
    buttonRstick = false;
    buttonHome = false;
    buttonCapture = false;

    LeftJoyRIGHT = false;
    LeftJoyLEFT = false;
    LeftJoyDOWN = false;
    LeftJoyUP = false;

    RightJoyRIGHT = false;
    RightJoyLEFT = false;
    RightJoyDOWN = false;
    RightJoyUP = false;

    HatUP = false;
    HatRIGHT = false;
    HatDOWN = false;
    HatLEFT = false;
  }

  if(Serial1.available() > 0) {
    String data = Serial1.readStringUntil('\n');

    if (data.startsWith("BT")) {
      data = data.substring(2);

      buttonY = data[0] - '0';
      buttonB = data[1] - '0';
      buttonA = data[2] - '0';
      buttonX = data[3] - '0';
      buttonL = data[4] - '0';
      buttonR = data[5] - '0';
      buttonZl = data[6] - '0';
      buttonZr = data[7] - '0';

      buttonMinus = data[8] - '0';
      buttonPlus = data[9] - '0';
      buttonLstick = data[10] - '0';
      buttonRstick = data[11] - '0';
      buttonHome = data[12] - '0';
      buttonCapture = data[13] - '0';

      LeftJoyRIGHT = data[14] - '0';
      LeftJoyLEFT = data[15] - '0';
      LeftJoyDOWN = data[16] - '0';
      LeftJoyUP = data[17] - '0';

      RightJoyRIGHT = data[18] - '0';
      RightJoyLEFT = data[19] - '0';
      RightJoyDOWN = data[20] - '0';
      RightJoyUP = data[21] - '0';

      HatUP = data[22] - '0';
      HatRIGHT = data[23] - '0';
      HatDOWN = data[24] - '0';
      HatLEFT = data[25] - '0';

      //Serial1.println(buttonA);
      releaseTime = millis();
    }
  }

  if (!dmpReady) return;

  while (!mpuInterrupt && fifoCount < packetSize) {
    if (mpuInterrupt && fifoCount < packetSize) {
      fifoCount = mpu.getFIFOCount();
    }
  }
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
    mpu.resetFIFO();
    fifoCount = mpu.getFIFOCount();
    //Serial.println(F("FIFO overflow!"));

  } else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    // Set left joystick
    leftJoyX = (ypr[2]-rollOffset) * ADC_Max/M_PI*SCALING;
    leftJoyY = (ypr[1]-pitchOffset) * ADC_Max/M_PI*SCALING;

    leftJoyX = map(leftJoyX, -512, 511, 255, 0);
    leftJoyY = map(leftJoyY, -512, 511, 255, 0);

    leftJoyX = constrain(leftJoyX, 0, 255);
    leftJoyY = constrain(leftJoyY, 0, 255);
  }

  // reset offset
  if (digitalRead(A0)) {
    onTime = millis();
  }
  else {
    // Long press Set offset IMU
    if ((millis() - onTime) > 1000) {
      pitchOffset = ypr[1];
      rollOffset = ypr[2];
    }
  }

  Joystick.setButton(0, buttonY); // Y
  Joystick.setButton(1, buttonB || !digitalRead(14)); // B
  Joystick.setButton(2, buttonA || !digitalRead(15)); // A
  Joystick.setButton(3, buttonX); // X
  Joystick.setButton(4, buttonL || !digitalRead(16)); // L
  Joystick.setButton(5, buttonR || !digitalRead(10)); // R
  Joystick.setButton(6, buttonZl); // ZL
  Joystick.setButton(7, buttonZr); // ZR
  Joystick.setButton(8, buttonMinus); // -
  Joystick.setButton(9, buttonPlus); // +
  Joystick.setButton(10, buttonLstick || !digitalRead(A0)); // Lstick
  Joystick.setButton(11, buttonRstick); // Rstick
  Joystick.setButton(12, buttonHome); // Home
  Joystick.setButton(13, buttonCapture); // capture


  if (LeftJoyRIGHT){
    Joystick.setXAxis(255); // Left joystick RIGHT
  } else if (LeftJoyLEFT){
    Joystick.setXAxis(0);   // Left joystick LEFT
  } else {
    Joystick.setXAxis(leftJoyX);
  }
  if (LeftJoyDOWN){
    Joystick.setYAxis(255); // Left joystick DOWN
  } else if (LeftJoyUP){
    Joystick.setYAxis(0);   // Left joystick UP
  } else {
    Joystick.setYAxis(leftJoyY);
  }
  if (RightJoyRIGHT){
    Joystick.setZAxis(255); // Right joystick RIGHT (camera left)
  } else if (RightJoyLEFT){
    Joystick.setZAxis(0);   // Right joystick LEFT (camera right)
  } else {
    Joystick.setZAxis(128);
  }
  if (RightJoyDOWN){
    Joystick.setRzAxis(255); // Right joystick DOWN (camera zoom out)
  } else if (RightJoyUP){
    Joystick.setRzAxis(0);  // Right joystick UP (camera zoom in)
  } else {
    Joystick.setRzAxis(128);
  }

  if (HatUP){
    Joystick.setHatSwitch(0); // UP
  } else if (HatUP && HatRIGHT){
    Joystick.setHatSwitch(45); // UP RIGHT
  } else if (HatRIGHT){
    Joystick.setHatSwitch(90); // RIGHT
  } else if (HatRIGHT && HatDOWN){
    Joystick.setHatSwitch(135); // RIGHT DOWN
  } else if (HatDOWN){
    Joystick.setHatSwitch(180); // DOWN
  } else if (HatDOWN && HatLEFT){
    Joystick.setHatSwitch(225); // DOWN LEFT
  } else if (HatLEFT){
    Joystick.setHatSwitch(270); // LEFT
  } else if (HatLEFT && HatUP){
    Joystick.setHatSwitch(315); // LEFT UP
  } else{
    Joystick.setHatSwitch(-1);
  }

  Joystick.sendState();
}

void fail() {
  while (1) {
    RXLED0;
    delay(250);
    RXLED1;
    delay(250);
  }
}
