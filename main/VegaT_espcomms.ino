#include <SoftwareSerial.h>
#include <string.h>
#include "VegaT_espcomms.h"
#include "bluetoothcomms.h"



///////////////////////////////////////////////////////////////////////
/*
Function :    calculateChecksum
Description : Function to calculate the checksum (one byte, including STX)
Arguments :   message,length
Return :      (uint8_t)(checksum % 256)
*/
void calculate_checksum(uint8_t *arr, int size, uint8_t *arr1) {
  if (arr == NULL || size <= 0) {
    return;
  }

  long long sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }

  char hex_sum[17];
  sprintf(hex_sum, "%llX", sum); // Use %llX for uppercase

  int hex_len = strlen(hex_sum);
  char last_two_hex[3] = "00";
  if (hex_len >= 2) {
    last_two_hex[0] = hex_sum[hex_len - 2];
    last_two_hex[1] = hex_sum[hex_len - 1];
    last_two_hex[2] = '\0';
  } else if (hex_len == 1) {
    last_two_hex[1] = hex_sum[0];
  }

  arr1[0] = (uint8_t)last_two_hex[0];
  arr1[1] = (uint8_t)last_two_hex[1];
}
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
/*
Function :    sendVegaTStatusRequest
Description : Function to send status request to VegaT
Arguments :   address,transaction numbers
Return :      void
*/
void sendVegaTstatusRequest(){
    uint8_t hexcmd[20]; // Allocate enough space
    int len = 0;
    

    hexcmd[len++] = 2; // STX

    hexcmd[len++] = 48; //Address
    hexcmd[len++] = 48;
    hexcmd[len++] = 49;

    hexcmd[len++] = 48; //Meter

    hexcmd[len++] = 51;
    hexcmd[len++] = 48; //Message Code: Status

    hexcmd[len++] = 48; //Counter
    hexcmd[len++] = 48; //Meter1
    hexcmd[len++] = 48; //Meter2

    hexcmd[len++] = 32;
    hexcmd[len++] = 32;
    hexcmd[len++] = 32;
    hexcmd[len++] = 32; //Reserved

    uint8_t arr1[2]; // Local arr1
    calculate_checksum(hexcmd, len, arr1); // Pass arr1

    hexcmd[len++] = arr1[1];
    hexcmd[len++] = arr1[0]; //Checksum

    hexcmd[len++] = 13;

    uart.write(hexcmd, len); 
    Serial.println("Command sent.");
    //Serial.print("CHK1= %d",arr1[1]);
    //Serial.print(arr1[0]);
    //Serial.print("CHK2=");
    //Serial.print(arr1[1]);
    
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

////////////////////////////////////////////////////////////////////////
/*
Function :    resetstopdeliverymessage
Description : Function to send stop delivery request to vega t
Arguments :   none
*/
void resetstopdeliverymessage(){
 uint8_t hexcmd[20]; // Allocate enough space
    int len = 0;
    

    hexcmd[len++] = 2; // STX

    hexcmd[len++] = 48; //Address
    hexcmd[len++] = 48;
    hexcmd[len++] = 49;

    hexcmd[len++] = 49; //Meter

    hexcmd[len++] = 52;
    hexcmd[len++] = 53; //Message Code: Stop Delivery

    hexcmd[len++] = 48; //Reset remote stop status  

    hexcmd[len++] = 32;
    hexcmd[len++] = 32;
    hexcmd[len++] = 32;
    hexcmd[len++] = 32; //Reserved

    uint8_t arr1[2]; // Local arr1
    calculate_checksum(hexcmd, len, arr1); // Pass arr1

    hexcmd[len++] = arr1[1];
    hexcmd[len++] = arr1[0]; //Checksum

    hexcmd[len++] = 13;

    uart.write(hexcmd, len); 
    Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/*
Function :    terminatebatchmessage
Description : Function to send stop delivery request to vega t
Arguments :   none
*/
void terminatebatchmessage(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x34, 0x36, 0x20, 0x20, 0x20, 0x20, 0x45, 0x41, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/*
Function :    leakedatarequest
Description : Function to send leak data request to vega t
Arguments :   none
*/
void leakedatarequest(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x35, 0x33, 0x43, 0x32, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/*
Function:    sendpresetmodificationrequestT() 
Description: Function to send preset modification request to VegaT
Arguments: 
Return:      receivedMessage
*/
void sendpresetmodificationrequest(){
   uint8_t hexcmd[25]; // Allocate enough space
    int len = 0;
    

    hexcmd[len++] = 2; // STX

    hexcmd[len++] = 48; //Address
    hexcmd[len++] = 48;
    hexcmd[len++] = 49;

    hexcmd[len++] = 49; //Meter

    hexcmd[len++] = 52;
    hexcmd[len++] = 51; //Message Code: Preset Modification 

    for(int i = 0; i<6; i++){
     hexcmd[len++] = preset[i];
    }

    uint8_t arr1[2]; // Local arr1
    calculate_checksum(hexcmd, len, arr1); // Pass arr1

    hexcmd[len++] = arr1[1];
    hexcmd[len++] = arr1[0]; //Checksum

    hexcmd[len++] = 13;

    uart.write(hexcmd, len); 
    Serial.println("Command sent.");

}
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
/*
Function :    batchdatarequest
Description : Function to send batch data request to vega t
Arguments :   none
*/
void batchdatarequest(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x35, 0x31, 0x41, 0x32, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
/*
Function :    batchdatastoredmessage
Description : Function to send batch data stored message to vega t
Arguments :   none
*/
void batchdatastoredmessage(){
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x35, 0x36, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x0D};
  uart.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
/*
Function:    receivemessageVegaT() 
Description: Function to receieve reply from VegaT
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
    Serial.println("/////////////////////////////////////");
    receivedData = " No data received";
  }

  delay(5000);
    return(receivedData);
 }

////////////////////////////////////////////////////////////////////////
