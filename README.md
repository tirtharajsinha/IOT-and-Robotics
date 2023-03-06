# Arduino & ESP Guide with Codes + Circuit Digram

<img src="banner.jpg" alt="">

## Microcontroller IOT Boards

- [Arduino boards](https://en.wikipedia.org/wiki/List_of_Arduino_boards_and_compatible_systems) (UNO,MEGA,NANO,LEONARDO etc)
- ESP8266 nodeMCU (Arduino + Micropython)
- ESP32 DevKit(Arduino + Micropython)

## Minimal Component Requirements

- One of the above board(Recommended : Arduino UNO)
- _USB type A_ to _USB type B_ connector for arduino
- led(Red,green,blue)
- jumpers(MtoM and MtoF)
- breadboard
- Register(220ohm,1Kohm,10Kohm)
- capacitor(220 microfarad,47 microfarad)
- Buzzer
- 8mm common anode RGB led
- Potentiometer

## Sensors and Modules(Required : based on project)

### Sensors

- HC-SR04 Ultrasonic distance sensor\*
- DHT11 temparature and humidity sensor\*
- BISS0001 PIR Motion sensor
- MPU-6050 3-Axis Accelerometer and Gyro Sensor
- _TTP223B_ Capacitive Touch Sensor Module
- LM393 Sound Detection Module
- IR receiver + Remote

### Wireless Modules

- ESP-01 ESP8266 Serial WIFI Module
- HC-05 Bluetooth Module

### Displays

- 16x2 LCD
- Single digit _7 segment_ display
- 0.96inch OLED I2C display

### Motors

- 12V 200 RPM DC Motor
- 28BYJ-48 Unipolar Stepper Motor
- SG90 Servo Motor (180° Rotation)

#### Motor Drivers

- L293D Motor Driver Shield(Arduino UNO/Mega)
- L293D Motor Driver Board for ESP8266 NodeMcu 12E
- L298N motor driver module
- ULN2003 Stepper Motor Driver
- A4988 driver Stepper Motor Driver

### Others

- 2N2222 transistor
- 2/4 - channel 5V relay module

## Softwere requirements

- [Arduino IDE(Latest version)](https://www.arduino.cc/en/software)
- [Arduino IDE(v1.8.3 if you have arduino nano)](https://downloads.arduino.cc/arduino-1.8.3-windows.exe)
- [Pycrarm(If micropython is used)](https://www.jetbrains.com/pycharm/)

## How to get started

**_Install the Arduino IDE & Clone this repository_**

```
git clone git@github.com:tirtharajsinha/arduino.git
```

1. Connect the arduino board via USB.
2. Open the arduino IDE
3. select the board and port number(something like `COM5`)
4. Now open `LED_BLINK/LED_BLINK.ino` in arduino ide.
5. Connect the circuit diagram available the .ino code location.
6. Open the arduino ide and validate and upload the script.
7. If you see led lights up and down periodically then you are good to go. othewise contact a experienced friend. if you friend refuses then your are fucked up, go search on youtube.

## Upstream the repository

```
git reset --hard origin/main
git remote add upstream https://github.com/tirtharajsinha/arduino.git
git fetch upstream
git checkout main
git merge upstream/main
```

If anytime you think you messed up with the original repo code then you can consider reset the rerository.

## Reset repository

```
git reset --hard origin/main
```

## Arduino libraries you need to get started

1. Adafruit Circuit Playground by Adafruit\*
2. Servo by Michael Margolis, Arduino
3. DHT sersor library by Adafruit\*
4. Adafruit Unified sensor by Adafruit\*
5. Firmata by firmata developers
6. WiFi by Arduino
7. LiquidCrystal by Arduino, Adafruit
8. Arduino_JSON by Arduino

## Diffrent type arduino boards

### Classic family

1. Arduino UNO R3
2. Arduino Mega 2560 Rev3
3. Arduino Leonardo
4. Arduino UNO Mini Limited Edition
5. Arduino Due
6. Arduino Micro
7. Arduino Zero
8. Arduino UNO WiFi Rev2

### Nano family

1. Arduino Nano 33 IoT
2. Arduino Nano RP2040 Connect
3. Arduino Nano 33 BLE Sense
4. Arduino Nano 33 BLE
5. Arduino Nano Every
6. Arduino Nano

### MKR family

1. Arduino MKR 1000 WiFi
2. Arduino MKR WiFi 1010
3. Arduino MKR FOX 1200
4. Arduino MKR WAN 1300
5. Arduino MKR WAN 1310
6. Arduino MKR GSM 1400
7. Arduino MKR NB 1500
8. Arduino MKR Vidor 4000
9. Arduino MKR Zero

### Portena family(Arduino Pro)

1. Portena H7
2. Portena X8
3. Portena Max Carrier(Carrier for portena)

## ESP based boards

1. ### esp8266

   - Start Arduino and open Preferences window.

   - Enter https://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.

   - Open Boards Manager from Tools > Board menu and find esp8266 platform.

   - Select the version you need from a drop-down box.

   - Click install button.

   - Don’t forget to select your ESP8266 board from Tools > Board menu after installation.

<hr>

2. ### esp32

   - Start Arduino and open Preferences window.

   - Enter https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.

   - Open Boards Manager from Tools > Board menu and find esp32 platform.

   - Select the version you need from a drop-down box.

   - Click install button.

   - Don’t forget to select your ESP32 board from Tools > Board menu after installation.

## Additional Libraries for esp8266/esp32

1. esp8266 by ESP8266 Community
2. ESP32 by Espressif Systems
3. [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
4. [ESPAsyncTCP for esp8266](https://github.com/me-no-dev/ESPAsyncTCP)
5. [AsyncTCP for esp32](https://github.com/me-no-dev/AsyncTCP)

## Micropython(Some selected boards are supported)

### Common boards that supported by micropython

1. all esp based boards.
2. Arduino nano RP2040 connect and Arduino Nano 33 BLE Sense
3. Arduino pro portena H7
4. all pyboards
5. Raspberry Pi pico & Pico W
6. BBC micro:bit v1
7. Adafruit Feather series

### Firmware and IDE Installation

- First read micropython [docs](https://micropython.org/download/) to check if your micropython support your board.

- Here booting micropython is only tested on esp boards so if you have diffrent board then try to search it online.

- Download the micropython firmware file :

  1. [esp32](https://micropython.org/download/esp32/)
  2. [esp8266](https://micropython.org/download/esp8266/)
  3. For others you can find [here](https://micropython.org/download/)

- Install the flash tool for esp boards :

  ```
  pip install esptool
  ```

  or

  ```
  pip3 install esptool
  ```

  verify installation with `esptool --help` command.

- Connect the esp board wit your computer and get the port number. It should be like `COM5 or /dev/ttyUSB0`

- Now open cmd where you downloaded the firmware/bin file.
- Run the following commands : <br>
  **Notice** : After entering the command before pressing `Enter` press the boot button in your esp board and press enter in your keyboard don't unpress until command executes.<br>
  **Erase previous firmware**
  ```
  esptool --port <PORT_NO> erase_flash
  ```
  **Install micropython firmware**
  ```
  esptool --port <PORT_NO> --baud 460800 write_flash --flash_size=detect 0 <FIRMWARE.bin>
  ```
- Now you need a IDE. I prefer pycharm for this. For Installation guide follow this [blog form pycharm](https://blog.jetbrains.com/pycharm/2018/01/micropython-plugin-for-pycharm/).

- To remove and get back to Arduino IDE, Run the following command :
  ```
  esptool --port <PORT_NO> erase_flash
  ```

## Setup Processing

> Processing is free, open source software based on Java. It was designed for the visual arts community for creating drawings, animations, and interactive programs. Download the latest version of Processing from [Processing.org](https://Processing.org). Select the right file according to your operating system. Processing is available for Linux, Mac OS X, and Windows. Extract all the files and click the Processing icon inside the folder to open it. The Processing IDE interface is very simple. The play icon in the toolbar allows you to compile and run the program and the stop icon will stop the program. In the bottom of the IDE there is a message area that, when you compile your program, gives you information about errors if any.

`It can visualize data receied through serial connection.`

- Notice: Don't use any serial monitor when processing script is running. Two program can't access the serial port at same time.

In Some Projects `processing` has been used. Like : [Radar](https://github.com/tirtharajsinha/arduino/tree/main/rader)

<hr>

<p style="font-size:20px; font-weight:600; text-align:right;"> -- By Tirtharaj Sinha</p>
