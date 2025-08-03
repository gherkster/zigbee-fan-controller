# Zigbee Fan Controller

A 433.92mhz RF fan controller using Zigbee and an ESP32-C6.

This can be used with Home Assistant to remotely control and automate an RF fan.

The transmitter used in this project is the STX882, though any 433.92mhz transmitter compatible with RCSwitch will probably work.

## Setup

Copy secret.example.ini in the base of the repo to secret.ini and populate the RF fan control codes.

These codes can be captured from an RF fan remote using the receiver code in src with a 433.92mhz receiver like the RX470-C.
