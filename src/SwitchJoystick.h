/*
  SwitchJoystick.h

  Copyright (c) 2017, Michele Perla for Hackerloop
  
  Based on the Joystick Library (https://github.com/MHeironimus/ArduinoJoystickLibrary) - Copyright (c) 2015-2017, Matthew Heironimus
  and on the Switch-Fighstick LUFA Proof-of-concept project (https://github.com/progmem/Switch-Fightstick) by Jason DeLeon
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef SWITCHJOYSTICK_h
#define SWITCHJOYSTICK_h

#include <DynamicHID/DynamicHID.h>

#if ARDUINO < 10606
#error The SwitchJoystick library requires Arduino IDE 1.6.6 or greater. Please update your IDE.
#endif // ARDUINO < 10606

#if ARDUINO > 10606
#if !defined(USBCON)
#error The SwitchJoystick library can only be used with a USB MCU (e.g. Arduino Leonardo, Arduino Micro, etc.).
#endif // !defined(USBCON)
#endif // ARDUINO > 10606

#if !defined(_USING_DYNAMIC_HID)

#warning "Using legacy HID core (non pluggable)"

#else // !defined(_USING_DYNAMIC_HID)

//================================================================================
//  Joystick (Gamepad)

#define JOYSTICK_DEFAULT_REPORT_ID         0x01
#define JOYSTICK_DEFAULT_BUTTON_COUNT        16
#define JOYSTICK_DEFAULT_AXIS_MINIMUM         0
#define JOYSTICK_DEFAULT_AXIS_MAXIMUM       255
#define JOYSTICK_DEFAULT_SIMULATOR_MINIMUM    0
#define JOYSTICK_DEFAULT_SIMULATOR_MAXIMUM 1023
#define JOYSTICK_DEFAULT_HATSWITCH_COUNT      1
#define JOYSTICK_HATSWITCH_COUNT_MAXIMUM      1
#define JOYSTICK_HATSWITCH_RELEASE           -1
#define JOYSTICK_TYPE_JOYSTICK             0x04
#define JOYSTICK_TYPE_GAMEPAD              0x05
#define JOYSTICK_TYPE_MULTI_AXIS           0x08

class SwitchJoystick_
{
private:

    // Joystick State
	uint8_t	                 _xAxis;
	uint8_t	                 _yAxis;
	uint8_t	                 _zAxis;
	uint8_t	                 _zAxisRotation;
	int16_t	                 _hatSwitchValue;
    uint8_t                 *_buttonValues = NULL;

    // Joystick Settings
    bool                     _autoSendState;
    uint8_t                  _buttonCount;
    uint8_t                  _buttonValuesArraySize = 0;
	uint8_t					 _hatSwitchCount;
	uint8_t					 _includeAxisFlags;

	uint8_t                  _hidReportId;
	uint8_t                  _hidReportSize; 

public:
	SwitchJoystick_();

	void begin(bool initAutoSendState = true);
	void end();

	// Set Axis Values
	void setXAxis(uint8_t value);
	void setYAxis(uint8_t value);
	void setZAxis(uint8_t value);
	void setRzAxis(uint8_t value);

	void setButton(uint8_t button, uint8_t value);
	void pressButton(uint8_t button);
	void releaseButton(uint8_t button);

	void setHatSwitch(int16_t value);

	void sendState();
	
	// sendState(uint8_t *data) is used to send raw data directly, useful for debugging
	// format is bit7		6		5		4		3		2		1		0
	// 1st byte: 	Zr		Zl		R		L		X		A		B		Y 
	// 2nd byte: 	x		x		Capture	Home	Rstick	Lstick	+		-
	// 3rd byte:	Hat Switch (values 0 from 7, 15 = neutral state);
	// 4th byte:	Left Joystick X axis (0 is left, 255 is right, 128 is center)
	// 5th byte:	Left Joystick Y axis (0 is up, 255 is down, 128 is center)
	// 6th byte:	Right Joystick X axis (0 is left, 255 is right, 128 is center)
	// 7th byte:	Right Joystick Y axis (0 is up, 255 is down, 128 is center)
	void sendState(uint8_t *data);
};

#endif // !defined(_USING_DYNAMIC_HID)
#endif // SWITCHJOYSTICK_h
