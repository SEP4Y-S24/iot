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


## For developers
- [Connection](./docs/connection.md): A small explanation of how connection takes place.
- [Encryption](./docs/encryption.md): This is how the device handles encryption.
- [Communication](./docs/communication.md): Here you can find the communication protocol.


#### Source of Information
- https://github.com/LauritsIvar/sep4_drivers/tree/hardware_by_ERL (for HC-SR04, DHT11 and ESP-01)
- https://github.com/chrisramsay/i2cmaster (Peter Fleury's i2c library)
- https://github.com/kokke/tiny-AES-c (for encryption)
