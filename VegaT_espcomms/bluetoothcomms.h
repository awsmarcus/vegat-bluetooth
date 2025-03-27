#ifndef _bluetoothcomms_h
#define _bluetoothcomms_h

String device_name = "ESP32-BT-Slave";
String receivedString = "";
String password = "Hectronic";  // Fixed password for authentication
bool isAuthenticated = false;
bool hasPrompted = false;  // Flag to check if the prompt has been sent

#define  Idle             0
#define  Transaction_Data 1
#define  vegatstatus      2
#define  Start            3
#define  Stop             4
#define  terminatebatch   5
#define  Leakdata         6
#define  Presetmod        7
#define  Batchdata        8
#define  Batchdatastored  9
#define  Resetstop        10

void Bluetoothinit();
void bluetoothAuthentication();
bool returnTrueAfterAuthentication();
void bluetoothcomm();

#endif
