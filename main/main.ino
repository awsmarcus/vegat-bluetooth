#include "BluetoothSerial.h"
#include <SoftwareSerial.h>
#include <stdio.h>
#include "bluetoothcomms.h"
#include "VegaT_espcomms.h"



SoftwareSerial uart = SoftwareSerial(16,17);
BluetoothSerial SerialBT;

void setup(){  
  uart.begin(9600);
  uart.listen();
  Serial.begin(115200);
  Bluetoothinit();
}

void loop() {
  // Check if the client is connected
  if (!SerialBT.hasClient() && isAuthenticated) {
    Serial.println("Client disconnected. Resetting authentication.");
    isAuthenticated = false; // Reset authentication state
    hasPrompted = false;     // Reset the prompt flag
  }

  // Prompt for password if a new client connects and not authenticated
  if (SerialBT.hasClient() && !isAuthenticated && !hasPrompted) {
    SerialBT.println("Enter password:");
    hasPrompted = true;
  }
bluetoothAuthentication();
if (isauth()){
 bluetoothcomm();
}
  delay(20);
}
