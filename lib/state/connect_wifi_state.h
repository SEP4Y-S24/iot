#pragma once
#include <state_coordinator.h>

/*
@brief Initialize the connect to Wifi state. During which the WiFi module is initialized and the connection to an access point is established.
if SSID and password are given the module will try to connect to the given access point and set it as default ap.
if SSID or password is NULL the module will check if it's already connected to an access point. If it is, it will continue to the next state.
if it is not connected to an access point it will start a server and wait to recieve ssid and password and then it will connect to the given access point.
*/
State connect_wifi_state_switch(char *ssid, char *pass);