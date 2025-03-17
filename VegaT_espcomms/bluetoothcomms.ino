#include "BluetoothSerial.h"
//#include <SoftwareSerial.h>
#include <string.h>

String device_name = "ESP32-BT-Slave";
String receivedString = "";

#define  Idle             0
#define  Transaction_Data 1
#define  status           2
#define  Start            3
#define  Stop             4

BluetoothSerial SerialBT;

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
      Serial.print("Received integer: ");
      Serial.println(receivedInt);

    switch (receivedInt) {

      case Transaction_Data:
             Serial.println("Transaction data enquired");
             Serial.println();
             //sendVegaTTransactionRequest("001", 1);
             receivemessageVegaT();
             SerialBT.println("Transaction Data");
             break;

      case status :
             Serial.println("Status Enquired");
             Serial.println();
             sendVegaTstatusRequest();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println("Status: ");
             SerialBT.print(bluetoothmessage);
              break;
      
      case Start :
             Serial.println("Start Batch");
             Serial.println();
             startbatchmessage();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println("Started");
              break;
      
      case Stop :
             Serial.println("Stop Batch");
             Serial.println();
             stopdeliverymessage();
             bluetoothmessage = receivemessageVegaT();
             SerialBT.println("Stopped");
              break;
    }
  }
///////////////////////////////////////////////////////////////////////