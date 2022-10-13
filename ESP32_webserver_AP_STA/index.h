#include "WString.h"
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>ESP32 Server</title>
    <style>
        * {
            padding: 0;
            margin: 0;
        }

        html {
            font-family: Helvetica;
            display: inline-block;
            margin: 0px;
            text-align: center;
        }

        body {
            background-color: #3B4252;
            display: flex;
            flex-direction:column;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
        }

        .nev {
            background-color: #2E3440;
            display: flex;
            height: 50px;
            align-items: center;
            position: fixed;
            justify-content: space-between;
            width: calc(100vw - 20px);
            top: 10px;
            left: 10px;
            border-radius: 20px;

        }

        .circle {
            background-color: #8FBCBB;
            width: 30px;
            height: 30px;
            border-radius: 15px;
            margin-right: 10px;
        }

        h1 {
            color: #ECEFF4;
            font-size: 18px;
            letter-spacing: 1px;
            margin-left: 20px;
            font-weight: 600;
        }

        h3 {
            color: #D8DEE9;
            margin-bottom: 50px;
            font-size: 20px;
        }

        .button {
            display: block;
            width: 80px;
            background-color: #5E81AC;
            border: none;
            color: #ECEFF4;
            padding: 13px 30px;
            text-decoration: none;
            font-size: 25px;
            margin: 0px auto 35px;
            cursor: pointer;
            border-radius: 7px;
        }

         .button-on {
            background-color: #488fe6;
        }

        .button-on:active {
            background-color: #488fe6;
        }

        .button-off {
            background-color: #517295;
        }

        .button-off:active {
            background-color: #5c748b;
        }

        p {
            font-size: 14px;
            color: #acb6ce;
            margin-bottom: 10px;
        }
    </style>
</head>

<body>
    <div class="nev">
        <h1>%SERVER_TITLE%</h1>
        <div class="circle"></div>
    </div>

    %BUTTON_TYPE%
</body>

</html>
)rawliteral";

String btn1on = "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1?state=ON\">ON</a>\n";
String btn1off = "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1?state=OFF\">OFF</a>";
String btn2on = "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2?state=ON\">ON</a>\n";
String btn2off = "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2?state=OFF\">OFF</a>\n";



