#include <RCSwitch.h>

/// @brief Enables receiving signals to determine fan control codes.
/// @param rcSwitch The RCSwitch instance.
/// @param pin The pin to listen for RF signals using RCSwitch.
void enableReceiver(RCSwitch& rcSwitch, int pin) {
  Serial.println("Starting rc-switch Receiver");

  rcSwitch.enableReceive(pin);

  Serial.println("rc-switch is listening on GPIO ");
  Serial.print(pin);

  Serial.println("Press buttons on your remote...");
}

/// @brief Receives an RF signal to determine fan control codes.
/// @param rcSwitch The RCSwitch instance.
void receive(RCSwitch& rcSwitch) {
  // Check if rc-switch has received a signal
  if (rcSwitch.available()) {

    long receivedValue = rcSwitch.getReceivedValue();
    if (receivedValue == 0) {
      rcSwitch.resetAvailable();
      return;
    }

    Serial.print("Received Value: ");
    Serial.print(receivedValue);
    Serial.print(" / Bit Length: ");
    Serial.print(rcSwitch.getReceivedBitlength());
    Serial.print(" / Protocol: ");
    Serial.println(rcSwitch.getReceivedProtocol());
    Serial.print("Binary: ");
    Serial.println(rcSwitch.getReceivedValue(), BIN);
    Serial.println("---------------------------------");

    rcSwitch.resetAvailable();
  }
}