# Arduino-controller
All of my arduino projects


## IOT Boards
- Arduino AVR board
- ESP8266 12 or 12e(Additonal board installation required)

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

## requirements
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


## Arduino libraries you need
1. Adafruit Circuit Playground by Adafruit
2. Servo by Michael Margolis, Arduino
3. DHT sersor library by Adafruit
4. Adafruit Unified sensor by Adafruit

## Additional Board managers

1. ### esp8266 
    - Start Arduino and open Preferences window.

    - Enter https://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.

    - Open Boards Manager from Tools > Board menu and find esp8266 platform.

    - Select the version you need from a drop-down box.

    - Click install button.

    - Don’t forget to select your ESP8266 board from Tools > Board menu after installation.

<hr>
- By Tirtharaj Sinha