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

// https://www.i2cdevlib.com/forums/topic/397-change-default-axes-orientation/
uint8_t dmpGetYawPitchRollOnEnd(float *data, Quaternion *q, VectorFloat *gravity) {
    // yaw: (about Y axis)
    data[0] = atan2(2*q -> x*q -> z - 2*q -> w*q -> y, 2*q -> w*q -> w + 2*q -> x*q -> x - 1);
    // pitch: (nose up/down, about Z axis)
    data[1] = atan(gravity -> x / sqrt(gravity -> z*gravity -> z + gravity -> y*gravity -> y));
    // roll: (tilt left/right, about X axis)
    data[2] = atan(gravity -> z / sqrt(gravity -> x*gravity -> x + gravity -> y*gravity -> y));
    return 0;
}

void loop() {
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
    dmpGetYawPitchRollOnEnd(ypr, &q, &gravity);

    // Set left joystick
    leftJoyX = (ypr[1]-rollOffset) * ADC_Max/M_PI*SCALING;
    leftJoyY = (ypr[2]-pitchOffset) * ADC_Max/M_PI*SCALING;

    leftJoyX = map(leftJoyX, -512, 511, 255, 0);
    leftJoyY = map(leftJoyY, -512, 511, 255, 0);

    leftJoyX = constrain(leftJoyX, 0, 255);
    leftJoyY = constrain(leftJoyY, 0, 255);
  }

  if (!digitalRead(15)){
    Joystick.pressButton(2); // A
  } else {
    Joystick.releaseButton(2);
  }
  if (!digitalRead(14)){
    Joystick.pressButton(1); // B
  } else {
    Joystick.releaseButton(1);
  }
  if (!digitalRead(16)){
    Joystick.pressButton(4); // L
  } else {
    Joystick.releaseButton(4);
  }
  if (!digitalRead(10)){
    Joystick.pressButton(5); // R
  } else{
    Joystick.releaseButton(5);
  }

  if (digitalRead(AO)) {
    onTime = millis();
    Joystick.pressButton(10); // Lstick
  }
  else {
    // Long press Set offset IMU
    if ((millis() - onTime) > 1000) {
      pitchOffset = ypr[2];
      rollOffset = ypr[1];
    }
    Joystick.releaseButton(10); // Lstick
  }

  Joystick.setXAxis(leftJoyX);
  Joystick.setYAxis(leftJoyY);

  Joystick.sendState();
  //delay(50); delay result in FIFO overflow!
}

void fail() {
  while (1) {
    RXLED0;
    delay(250);
    RXLED1;
    delay(250);
  }
}
