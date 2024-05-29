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

## Source of Information
- https://github.com/LauritsIvar/sep4_drivers/tree/hardware_by_ERL
