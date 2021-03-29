# Arduino SwitchJoystick Library
#### Version 1.0.0
This library can be used with Arduino IDE 1.6.6 (or above) to add one or more joysticks (or gamepads) to the list of HID devices an [Arduino Leonardo](https://www.arduino.cc/en/Main/ArduinoBoardLeonardo) or [Arduino Micro](https://www.arduino.cc/en/Main/ArduinoBoardMicro) (or any Arduino clone that is based on the ATmega32u4) can support. This will not work with Arduino IDE 1.6.5 (or below) or with non-32u4 based Arduino devices (e.g. Arduino UNO, Arduino MEGA, etc.).

Based on the Arduino Joystick Library (https://github.com/MHeironimus/ArduinoJoystickLibrary) by Matthew Heironimus and on the Switch LUFA Proof-of-Concept (https://github.com/progmem/Switch-Fightstick) by Jason DeLeon.
## Features
The gamepad has the following features:
- 16 buttons (14 used)
- 1 Hat Switch
- X and Y Axis(Left Stick), 8-bit precision
- Z and Z Axis Rotation (Rigth Stick), 8-bit precision

## Installation Instructions
Since you need to modify a file that will affect all other Arduino boards used in your system, it is STRONGLY suggested to install this library in a separate Arduino installation.
Copy the `SwitchJoystick` folder to the Arduino libraries folder. Once the folder has been copied, the SwitchJoystick library should appear in the Arduino IDE list of libraries. The example should also appear in the examples menu in the Arduino IDE.
Open the `boards.txt` file under `hardware\arduino\avr` and append to it the following entry:
```
myboard.name=SwitchJoystick
myboard.vid.0=0x0F0D
myboard.pid.0=0x8092
myboard.vid.1=0x0F0D
myboard.pid.1=0x0092

myboard.upload.tool=avrdude
myboard.upload.protocol=avr109
myboard.upload.maximum_size=28672
myboard.upload.maximum_data_size=2560
myboard.upload.speed=57600
myboard.upload.disable_flushing=true
myboard.upload.use_1200bps_touch=true
myboard.upload.wait_for_upload_port=true

myboard.bootloader.tool=avrdude
myboard.bootloader.low_fuses=0xff
myboard.bootloader.high_fuses=0xd8
myboard.bootloader.extended_fuses=0xcb
myboard.bootloader.file=caterina/Caterina-Leonardo.hex
myboard.bootloader.unlock_bits=0x3F
myboard.bootloader.lock_bits=0x2F

myboard.build.mcu=atmega32u4
myboard.build.f_cpu=16000000L
myboard.build.vid=0x0F0D
myboard.build.pid=0x0092
myboard.build.usb_product="POKKEN CONTROLLER"
myboard.build.board=AVR_LEONARDO
myboard.build.core=arduino
myboard.build.variant=leonardo
myboard.build.extra_flags={build.usb_flags}
```
You can use this board entry as a template for other boards, in case you're not using an Arduino Leonardo; the important things are that the board must be ATmega32u4-based, that you replace `myboard` with a unique name, and that you keep the `vid`, `pid`, and `usb_product` as in this entry.
Finally, open the `platform.txt` file under `hardware\arduino\avr`, and at the end of the file replace `build.usb_manufacturer="Unknown"` with `build.usb_manufacturer="HORI CO.,LTD."`.

## Alternative Menu Installation
Do the same procedure but in the `boards.txt` file under `hardware\arduino\avr` append to it the following entry:
```
menu.build_variant=Build Variant
leonardo.menu.build_variant.leonardo=Leonardo

leonardo.menu.build_variant.leonardo_switch=SwitchJoystick

leonardo.menu.build_variant.leonardo_switch.name=SwitchJoystick
leonardo.menu.build_variant.leonardo_switch.vid.0=0x0F0D
leonardo.menu.build_variant.leonardo_switch.pid.0=0x8092
leonardo.menu.build_variant.leonardo_switch.vid.1=0x0F0D
leonardo.menu.build_variant.leonardo_switch.pid.1=0x0092

leonardo.menu.build_variant.leonardo_switch.upload.tool=avrdude
leonardo.menu.build_variant.leonardo_switch.upload.protocol=avr109
leonardo.menu.build_variant.leonardo_switch.upload.maximum_size=28672
leonardo.menu.build_variant.leonardo_switch.upload.maximum_data_size=2560
leonardo.menu.build_variant.leonardo_switch.upload.speed=57600
leonardo.menu.build_variant.leonardo_switch.upload.disable_flushing=true
leonardo.menu.build_variant.leonardo_switch.upload.use_1200bps_touch=true
leonardo.menu.build_variant.leonardo_switch.upload.wait_for_upload_port=true

leonardo.menu.build_variant.leonardo_switch.bootloader.tool=avrdude
leonardo.menu.build_variant.leonardo_switch.bootloader.low_fuses=0xff
leonardo.menu.build_variant.leonardo_switch.bootloader.high_fuses=0xd8
leonardo.menu.build_variant.leonardo_switch.bootloader.extended_fuses=0xcb
leonardo.menu.build_variant.leonardo_switch.bootloader.file=caterina/Caterina-Leonardo.hex
leonardo.menu.build_variant.leonardo_switch.bootloader.unlock_bits=0x3F
leonardo.menu.build_variant.leonardo_switch.bootloader.lock_bits=0x2F

leonardo.menu.build_variant.leonardo_switch.build.mcu=atmega32u4
leonardo.menu.build_variant.leonardo_switch.build.f_cpu=16000000L
leonardo.menu.build_variant.leonardo_switch.build.vid=0x0F0D
leonardo.menu.build_variant.leonardo_switch.build.pid=0x0092
leonardo.menu.build_variant.leonardo_switch.build.usb_product="POKKEN CONTROLLER"
leonardo.menu.build_variant.leonardo_switch.build.board=AVR_LEONARDO
leonardo.menu.build_variant.leonardo_switch.build.core=arduino
leonardo.menu.build_variant.leonardo_switch.build.variant=leonardo
leonardo.menu.build_variant.leonardo_switch.build.extra_flags={build.usb_flags}

leonardo.menu.build_variant.leonardo_switch.build.usb_manufacturer="HORI CO.,LTD."
```
Restart the IDE and now in the board Arduino Leonardo menu you should see a "Buid Variant" menu.

## Example
The following example Arduino sketch file is included in this library:

- `JoystickTest` - Simple test of the SwitchJoystick library. Use 12 buttons with pullups connected to pins A0 to A3 and to pins 4 to 15 to control all the joystick features.

- `JoystickIMUTest` - Simple test of the SwitchJoystick library. Use an MPU6050 as a joystick.

## Mapping

|  Button |  Switch |
| ------- | ------- |
|       0 |       Y |
|       1 |       B |
|       2 |       A |
|       3 |       Z |
|       4 |       L |
|       5 |       R |
|       6 |      Zl |
|       7 |      Zr |
|       8 |       - |
|       9 |       + |
|      10 |  Lstick |
|      11 |  Rstick |
|      12 |    Home |
|      13 | Capture |

|    Axis |   Switch |
| ------- | -------- |
|     X,Y |  LeftJoy |
|    Z,Rz | RightJoy |

| Hat/D-pad |  Switch |
| --------- | ------- |
|         0 |      UP |
|        90 |   RIGHT |
|       180 |    DOWN |
|       270 |    LEFT |
|        -1 | RELEASE |

## SwitchJoystick Library API
The following API is available if the SwitchJoystick library in included in a sketch file.

### SwitchJoystick\_()
Constructor used to initialize and setup the Joystick.

### SwitchJoystick.begin(bool initAutoSendState)
Starts emulating a game controller connected to a Nintendo Switch. By default, all methods update the game controller state immediately. If `initAutoSendState` is set to `false`, the `sendState` method must be called to update the game controller state.

### SwitchJoystick.end()
Stops the game controller emulation to a connected Nintendo Switch (not actually implemented).

### SwitchJoystick.setXAxis(uint8_t value)
Sets the X axis value. The range is

### Joystick.setYAxis(uint8_t value)
Sets the Y axis value.

### Joystick.setZAxis(uint8_t value)
Sets the Z axis value.

### Joystick.setRzAxis(uint8_t value)
Sets the Z axis rotation value.

### Joystick.setButton(uint8_t button, uint8_t value)
Sets the state (`0` or `1`) of the specified button (range: `0` - `15`). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.). The value is `1` if the button is pressed and `0` if the button is released.

### Joystick.pressButton(uint8_t button)
Press the indicated button (range: `0` - `15`). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.).

### Joystick.releaseButton(uint8_t button)
Release the indicated button (range: `0` - `15`). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.).

### Joystick.setHatSwitch(int16_t value)
Sets the value of the D-pad (hat switch). The value is from 0° to 360°, but in 45° increments. Any value less than 45° will be rounded down (i.e. 44° is rounded down to 0°, 89° is rounded down to 45°, etc.). Set the value to `JOYSTICK_HATSWITCH_RELEASE` or `-1` to release the hat switch.

### Joystick.sendState()
Sends the updated joystick state to the Nintendo Switch. Only needs to be called if `AutoSendState` is `false` (see `SwitchJoystick.begin` for more details).