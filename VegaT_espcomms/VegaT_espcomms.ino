#include <SoftwareSerial.h>
#include <string.h>


SoftwareSerial uart = SoftwareSerial(16,17);



///////////////////////////////////////////////////////////////////////
/*
Function :    calculateChecksum
Description : Function to calculate the checksum (one byte, including STX)
Arguments :   message,length
Return :      (uint8_t)(checksum % 256)
*/
uint8_t calculateChecksum(const char* message, int length) {
  uint16_t checksum = 0;

  for (int i = 0; i < length; i++) {
    checksum += (uint8_t)message[i];
  }

  return (uint8_t)(checksum % 256);
}
////////////////////////////////////////////////////////////////////////
/*
Function :    sendVegaTStatusRequest
Description : Function to send status request to VegaT
Arguments :   address,transaction numbers
Return :      void
*/
void sendVegaTstatusRequest(){
    byte message[] = {0x02, 0x30, 0x30, 0x31, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x36, 0x33, 0x0D};
  uart.write(message, sizeof(message));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
/*
Function :    sendVegaTTransactionRequest
Description : Function to send transaction data request to VegaT
Arguments :   address,transaction numbers
Return :      void

void sendVegaTTransactionRequest(const char* address, uint32_t transactionNumber) {
  char message[30];
  int len = 0;

  message[len++] = 0x02; // STX

  // Address (3 digits)
  strcpy(message + len, address);
  len += strlen(address);

  message[len++] = '0'; // Meter (0 = System)
  message[len++] = '6'; // Message Code (61) first digit
  message[len++] = '1'; // Message Code (61) second digit

  message[len++] = '1'; // System Status (1 = Not Requested)
  message[len++] = '0'; // Meter 1 Status (0 = Requested)
  message[len++] = '1'; // Meter 2 Status (1 = Not Requested)

  // Transaction number (6 digits)
  char transactionStr[7];
  sprintf(transactionStr, "%06lu", transactionNumber);
  strcpy(message + len, transactionStr);
  len += strlen(transactionStr);

  // Calculate Checksum (one byte, including STX)
  uint8_t checksum = calculateChecksum(message, len); // Include STX

  // Checksum (2 hex characters)
  char checksumHex[3];
  sprintf(checksumHex, "%02X", checksum);

  message[len++] = checksumHex[0];
  message[len++] = checksumHex[1];

  message[len++] = 0x0D; // ETX

  // Debugging output (ASCII)
  Serial.print("Sent message HEX: ");
  for (int i = 0; i < len; i++) {
    Serial.print(message[i],HEX);
    Serial.print(" ");

  }
  Serial.println();
  Serial.print("ASCII: ");
  for (int i = 0; i < len; i++) {
    Serial.print(message[i]);
    Serial.print(" ");
  }

  Serial.println();

  // Send over UART
  uart.write(message, len);
}*/
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
/*
Function :    startbatchmessage
Description : Function to send start batch request to vgea t 
Arguments :   none
Return :      void
*/
void startbatchmessage(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x34, 0x34, 0x20, 0x20, 0x20, 0x20, 0x43, 0x41, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/*
Function :    stopdeliverymessage
Description : Function to send stop delivery request to vega t
Arguments :   none
*/
void stopdeliverymessage(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x34, 0x35, 0x31, 0x20, 0x20, 0x20, 0x20, 0x45, 0x44, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}



////////////////////////////////////////////////////////////////////////
/*
Function:    receivemessageVegaT() 
Description: Function to send receieve reply from VegaT
Arguments: 
Return:      receivedMessage
*/
String receivemessageVegaT() {
  String receivedData = "";
  unsigned long timeout = millis() + 5000;

 
  while (millis() < timeout) {
    if (uart.available()) {
      receivedData += (char)uart.read();
    }
  }

 
  if (receivedData.length() > 0) {
    Serial.print("Received Data: ");
    Serial.println(receivedData);
  } else {
    Serial.println("No data received.");
  }

  delay(5000);
    return(receivedData);
 }

////////////////////////////////////////////////////////////////////////


