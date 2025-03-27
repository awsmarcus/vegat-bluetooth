#include <HardwareSerial.h>


HardwareSerial mySerial(1);

void setup() {
 
  Serial.begin(115200);

 
  mySerial.begin(9600, SERIAL_8N1, 16, 17);
  
 
  delay(2000);

 
  Serial.println("Starting communication");
}

void loop() {
 
  byte hexCmd[] = {0x02, 0x30, 0x30, 0x31, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x36, 0x33, 0x0D};
  
 
  mySerial.write(hexCmd, sizeof(hexCmd));  
  Serial.println("Command sent.");
  
  
  String receivedData = "";
  unsigned long timeout = millis() + 5000;

 
  while (millis() < timeout) {
    if (mySerial.available()) {
      receivedData += (char)mySerial.read();
    }
  }

 
  if (receivedData.length() > 0) {
    Serial.print("Received Data: ");
    Serial.println(receivedData);
  } else {
    Serial.println("No data received.");
  }

  delay(5000);
}

