# Arduino-controller
All of my Arduino & ESP projects


## IOT Boards
- Arduino AVR boards
- ESP8266 12 or 12e(Additonal board installation required)
- esp32 Wroom devkit(Additional board installation required)

## minimal component requirements
- led(Red green blue)
- jumpers(MtoM and MtoF)
- breadboard
- usb connector for arduino
- register(220ohm,1Kohm,10Kohm)

## sensors and modules(not mendatory)
- ultrasonic distance sensor
- DHT11 temparature and humidity sensor
- PIR Motion sensor
- Servo motor
- ESP8266 wifi module
- bluetooth module
- buzzer
- touch sersor
- 16x2 LCD
- 7 segment display
- potentiometer
- stepper motor
- motor controller shield
- capacitor(220 microfarad,47microfarad)
- IR receiver
- IR remote
- 8mm common anode RGB led

## Softwere requirements
- Arduino IDE


## How to get started
> Clone this repository
```
git clone git@github.com:tirtharajsinha/arduino.git
```

1. Connect the arduino board
2. open the arduino IDE
3. select the board and port number(something like ```COM5```)
4. Now open any .ino in arduino ide.
5. install the required libraries listed below.
6. Connect the circuit available the .ino code location.
7. Open the arduino ide and validate and upload the script.
8. If you see one led lights up then you are good to go. othewise contact maintainer. if maintainer refuses then you are fucked up. 

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

## Arduino libraries you need
1. Adafruit Circuit Playground by Adafruit
2. Servo by Michael Margolis, Arduino
3. DHT sersor library by Adafruit
4. Adafruit Unified sensor by Adafruit


## Diffrent type arduino boards
### classic family
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



## Additional Board managers

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

    - Don’t forget to select your ESP8266 board from Tools > Board menu after installation.


## Additional Libraries for esp8266/esp32
1. esp8266 by ESP8266 Community
2. ESP32 by Espressif Systems
3. [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
4. [ESPAsyncTCP for esp8266](https://github.com/me-no-dev/ESPAsyncTCP)
5. [AsyncTCP for esp32](https://github.com/me-no-dev/AsyncTCP)



<hr>

## By Tirtharaj Sinha