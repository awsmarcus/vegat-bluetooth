#include "BluetoothSerial.h"
//#include <SoftwareSerial.h>
#include <string.h>
#include "VegaT_espcomms.h"
#include "bluetoothcomms.h"


///////////////////////////////////////////////////////////////////////
/*
Function :    Bluetoothinit 
Description : Function to initialize bluetooth
Arguments :   none
Return :      void
*/
void Bluetoothinit(){
  // Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

//BluetoothSerial SerialBT;

  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/*
Function :    bluetoothAuthentication 
Description : Function for bluetooth password
Arguments :   none
Return :      void
*/
void bluetoothAuthentication() {
  if (SerialBT.available()) {
    String receivedMessage = SerialBT.readString();
    receivedMessage.trim();  // Remove leading/trailing spaces

    if (receivedMessage.isEmpty()) {
      return;  // Ignore invalid input
    }

    Serial.println("Received: " + receivedMessage);

    if (!isAuthenticated) {
      if (receivedMessage == password) {
        isAuthenticated = true;
        Serial.println("Authentication successful.");
        SerialBT.println("Authentication successful. You now have access.");
      } else {
        Serial.println("Invalid password. Access denied.");
        SerialBT.println("Invalid password. Please try again.");
        hasPrompted = false;  // Allow retry by resetting the prompt flag
      }
    }
  }
}
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/*
Function :    isauth  
Description : Function to return isAuthentcated boolean
Arguments :   none
Return :      isAuthenticated
*/
bool isauth(){
  return isAuthenticated;
}
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/*
Function :    bluetoothcomm
Description : Function to handle bluetooth comms 
Arguments :   none
Return :      void
*/
void bluetoothcomm(){
//if (SerialBT.available()) { 
    String bluetoothmessage;
    String input = SerialBT.readStringUntil('\n'); 
    // Option 1: Directly parse the incoming data into an integer
    int receivedInt  = input.toInt();  
      Serial.println("/////////////////////////////////////");
      Serial.print("Received integer: ");
      Serial.println(receivedInt);

    switch (receivedInt) {

      /*case Transaction_Data: // not implemented right now 
             //Serial.println();
             //sendVegaTTransactionRequest("001", 1);
             receivemessageVegaT();
             SerialBT.println("Transaction Data");
             */break;

      case vegatstatus :
             //Serial.println("/////////////////////////////////////");
             Serial.println("Status Enquired");
             //Serial.println();
             sendVegaTstatusRequest();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println("Status: ");
             SerialBT.print(bluetoothmessage);
              break;
      
      case Start :
              //Serial.println("/////////////////////////////////////");
             Serial.println("Start Batch");
             //Serial.println();
             startbatchmessage();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;
      
      case Stop :
              //Serial.println("/////////////////////////////////////");
             Serial.println("Stop Batch");
             //Serial.println();
             stopdeliverymessage();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;

      case terminatebatch :
             //Serial.println("/////////////////////////////////////");
            Serial.println("Terminate Batch");
             //Serial.println();
             terminatebatchmessage();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;    

      case Leakdata :
              //Serial.println("/////////////////////////////////////");
             Serial.println("leak data requested");
             //Serial.println();
             leakedatarequest();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;

      case Presetmod : {
            Serial.println("Preset modification");
              SerialBT.println("Enter preset amount (6 digits) :");
             String presetinput = SerialBT.readStringUntil('\n'); 
             for(int i=0;i<6;i++){
             preset[i] = presetinput[i] - '0';}
            sendpresetmodificationrequest();
            bluetoothmessage = receivemessageVegaT();
            SerialBT.println(bluetoothmessage);
              break; 
      }      
      
      case Batchdata: 
           Serial.println("Batch data requested");
           batchdatarequest();
           bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;

      case Batchdatastored: 
           Serial.println("Batch data stored");
           batchdatastoredmessage(); 
           bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break;   

      case Resetstop:
          Serial.println("Reset Stop");
           resetstopdeliverymessage(); 
           bluetoothmessage = receivemessageVegaT();
             SerialBT.println(bluetoothmessage);
              break; 
                        
    }
  }
///////////////////////////////////////////////////////////////////////

