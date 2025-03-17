//#include "BluetoothSerial.h"
//#include <SoftwareSerial.h>
//#include <string.h>
#include <stdio.h>
#include "esp_attr.h"

bool connectionstatus = false;

void setup() {  
  uart.begin(9600);
  uart.listen();
  Serial.begin(115200);
  Bluetoothinit();
}

void loop() {
  //bool connectionstatus;
   if(connectionstatus= false ){
   if(SerialBT.connected()){
    Serial.println("Connected to mobile device");
    connectionstatus= true ;
  }
   }
  if (SerialBT.available()) { 
    bluetoothcomm();
  }
  
  delay(20);
}
