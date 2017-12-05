/*
  Joystick.h

  Copyright (c) 2015-2017, Matthew Heironimus

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

#ifndef JOYSTICK_h
#define JOYSTICK_h

#include <DynamicHID/DynamicHID.h>

#if ARDUINO < 10606
#error The Joystick library requires Arduino IDE 1.6.6 or greater. Please update your IDE.
#endif // ARDUINO < 10606

#if ARDUINO > 10606
#if !defined(USBCON)
#error The Joystick library can only be used with a USB MCU (e.g. Arduino Leonardo, Arduino Micro, etc.).
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

class Joystick_
{
private:

    // Joystick State
	int8_t	                 _xAxis;
	int8_t	                 _yAxis;
	int8_t	                 _zAxis;
	int8_t	                 _zAxisRotation;
	int16_t	                 _hatSwitchValue;
    uint8_t                 *_buttonValues = NULL;

    // Joystick Settings
    bool                     _autoSendState;
    uint8_t                  _buttonCount;
    uint8_t                  _buttonValuesArraySize = 0;
	uint8_t					 _hatSwitchCount;
	uint8_t					 _includeAxisFlags;
	int8_t                  _xAxisMinimum = JOYSTICK_DEFAULT_AXIS_MINIMUM;
	int8_t                  _xAxisMaximum = JOYSTICK_DEFAULT_AXIS_MAXIMUM;
	int8_t                  _yAxisMinimum = JOYSTICK_DEFAULT_AXIS_MINIMUM;
	int8_t                  _yAxisMaximum = JOYSTICK_DEFAULT_AXIS_MAXIMUM;
	int8_t                  _zAxisMinimum = JOYSTICK_DEFAULT_AXIS_MINIMUM;
	int8_t                  _zAxisMaximum = JOYSTICK_DEFAULT_AXIS_MAXIMUM;
	int8_t                  _rzAxisMinimum = JOYSTICK_DEFAULT_AXIS_MINIMUM;
	int8_t                  _rzAxisMaximum = JOYSTICK_DEFAULT_AXIS_MAXIMUM;

	uint8_t                  _hidReportId;
	uint8_t                  _hidReportSize; 

public:
	Joystick_();

	void begin(bool initAutoSendState = true);
	void end();

	// Set Axis Values
	void setXAxis(int8_t value);
	void setYAxis(int8_t value);
	void setZAxis(int8_t value);
	void setRzAxis(int8_t value);

	void setButton(uint8_t button, uint8_t value);
	void pressButton(uint8_t button);
	void releaseButton(uint8_t button);

	void setHatSwitch(int16_t value);

	void sendState();
	void sendState(uint8_t *data);
};

#endif // !defined(_USING_DYNAMIC_HID)
#endif // JOYSTICK_h
