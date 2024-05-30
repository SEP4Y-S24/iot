# IoT Device

[![Tests](https://github.com/SEP4Y-S24/iot/actions/workflows/build.yaml/badge.svg)](https://github.com/SEP4Y-S24/iot/actions/workflows/build.yaml)
[![codecov](https://codecov.io/gh/SEP4Y-S24/iot/branch/main/graph/badge.svg?token=ZXVQMEAXOZ)](https://codecov.io/gh/SEP4Y-S24/iot)
![GitHub Latest Release)](https://img.shields.io/github/v/release/SEP4Y-S24/iot?logo=github)

## Specifications

- Arduino ATMega2560
- Sensors
  - DS3231 (RTC module)
  - DHT11 (Temperature and Humidity)
  - HC-SR04 (Ultrasonic)
  - MQ135 (Gas and CO2)*
  - SCD40 (CO2)*
- Peripherals 
  - ESP-01 (Wifi)
  - LCD 16x2 (Screen)

*Simulated for now

## Prototype 
![photo_2024-05-29_16-26-59](https://github.com/SEP4Y-S24/iot/assets/114725463/b3a906ec-1898-42b3-a3d4-dfaeff6712ee)

## How to connect...

1. Connect both devices to the same Wi-Fi
   
_Note: Use hot-spot or other network which does not require authorization_

2. Authenticate with backend 
3. Press the middle button to see the unique key for the clock
4. Input said key on the website

## More detailed connection explanation

First time connection:

1) A clock connects to a server and handles encryption setup
2) The clock sends to the server empty message with action type - AU(authentication)
example: AU|0||

3) The server generates a unique key and sends a it as a response with status code 3 Unauthenticated 
Example: AU|20|x14sfpun6ldpgt1l6p82|

4) The clock displays the unique key on a display
5) A user logs in to the web app and inputs the unique key.
6) The web app sends the unique key to the server
7) The server compares the received code with the one it sent to the clock and if they matches it associate the clock with the user.
8) Server sends message with action type KV (Key verified) to clock.
example: KV|0||
9) The clock saves the key and starts to work as normal.
    
Next time connection:
1) The clock connects to server and handle encryption setup
2) The clock sends to server the saved unique key in message with action type - AU(authentication)
example: AU|20|x14sfpun6ldpgt1l6p82|
3) The server knowing the clock answers with status code 1 - OK AU|1|0||
4) The clock starts to work as normal.

## Source of Information
- https://github.com/LauritsIvar/sep4_drivers/tree/hardware_by_ERL (for HC-SR04, DHT11 and ESP-01)
- https://github.com/chrisramsay/i2cmaster (Peter Fleury's i2c library)
- https://github.com/kokke/tiny-AES-c (for encryption)
