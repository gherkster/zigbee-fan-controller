#include <Arduino.h>
#include <RCSwitch.h>
#include "Zigbee.h"

// The ESP32 pin connected to the STX882 DATA pin
#define RF_TRANSMIT_PIN 17

#define ZIGBEE_FAN_ENDPOINT 10

RCSwitch mySwitch = RCSwitch();

void sendFanCommand(int command) {
  int bitLength = 12;

  Serial.print("Transmitting RF Code: ");
  Serial.println(command);
  
  mySwitch.send(command, bitLength);
}

void handleFanControl(ZigbeeFanMode fanMode) {
  Serial.print("Received Zigbee Fan Mode: ");
  
  switch (fanMode) {
    case FAN_MODE_OFF:
      Serial.println("OFF");
      sendFanCommand(FAN_CONTROL_CODE_OFF);
      break;
    case FAN_MODE_LOW:
      Serial.println("LOW");
      sendFanCommand(FAN_CONTROL_CODE_LOW);
      break;
    case FAN_MODE_MEDIUM:
      Serial.println("MEDIUM");
      sendFanCommand(FAN_CONTROL_CODE_MEDIUM);
      break;
    case FAN_MODE_HIGH:
      Serial.println("HIGH");
      sendFanCommand(FAN_CONTROL_CODE_HIGH);
      break;
    default:
      Serial.println("Unsupported mode: ");
      Serial.print(fanMode);
      break;
  }
}

ZigbeeFanControl zbFan(ZIGBEE_FAN_ENDPOINT);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting Zigbee to 433MHz Fan Bridge (Native Fan Mode)...");

  mySwitch.enableTransmit(RF_TRANSMIT_PIN);

  // Initialize 433MHz RF Transmitter
  mySwitch.setPulseLength(240);
  mySwitch.setRepeatTransmit(16);
  mySwitch.setProtocol(11);

  Serial.println("RF Transmitter Initialized.");

  zbFan.setManufacturerAndModel("ESP32-C6", "FanBridge");
  zbFan.setFanModeSequence(FAN_MODE_SEQUENCE_LOW_MED_HIGH);
  zbFan.onFanModeChange(handleFanControl);

  Zigbee.addEndpoint(&zbFan);

  Serial.println("Zigbee Fan Endpoint Initialized.");

  if (!Zigbee.begin()) {
    Serial.println("FATAL: Zigbee failed to start. Restarting...");
    ESP.restart();
  }
  Serial.println("Zigbee stack started. Waiting for connection...");

  while (!Zigbee.connected()) {
    delay(500);
  }
  Serial.println("Zigbee connected to network!");
}

void loop() { }
