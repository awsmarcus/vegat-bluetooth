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




////////////////////////////////////////////////////////////////////////
/*
Function :    sendVegaTTransactionRequest
Description : Function to send transaction data request to VegaT
Arguments :   address,transaction numbers
Return :      void
*/
void sendVegaTTransactionRequest(const char* address, uint32_t transactionNumber) {
  char message[30];
  int len = 0;

  //message[len++] = 0x02; // STX

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

  //message[len++] = 0x0D; // ETX

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
  uart.print("02");
  uart.print(" ");
  for (int i = 0; i < len; i++) {
  uart.print(message[i],HEX);
  uart.print(" ");}// Send the message 
   uart.print("0D");
}
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////
/*
Function:    receivemessageVegaT() 
Description: Function to send receieve reply from VegaT
Arguments: 
Return:      receivedMessage
*/
void receivemessageVegaT() {
   if (uart.available() > 0) {
    char receivedMessage[50];
    int len = 0;
    unsigned long startTime = millis();

    while (uart.available() > 0 && len < sizeof(receivedMessage) - 1 && (millis() - startTime) < 500) {
        receivedMessage[len++] = uart.read();
        delay(10); // Allow time for additional bytes
    }
    receivedMessage[len] = '\0'; // Null-terminate string

    // Print received message as HEX
    Serial.print("Received message (HEX): ");
    for (int i = 0; i < len; i++) {
        Serial.print((uint8_t)receivedMessage[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Print received message as ASCII
    Serial.print("Received message (ASCII): ");
    Serial.println(receivedMessage);

    //return(receivedMessage);
 }
}
////////////////////////////////////////////////////////////////////////


