# IoT Device

[![Tests](https://github.com/SEP4Y-S24/iot/actions/workflows/build.yaml/badge.svg)](https://github.com/SEP4Y-S24/iot/actions/workflows/build.yaml)
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
## How to connect...

1. Connect both devices to the same Wi-Fi
   
_Note: Use hot-spot or other network which does not require authorization_

2. Authentificate with backend 
3. Press middle button to see unique key for the clock
4. Input said key in the front end

## Source of Information
- https://github.com/LauritsIvar/sep4_drivers/tree/hardware_by_ERL
