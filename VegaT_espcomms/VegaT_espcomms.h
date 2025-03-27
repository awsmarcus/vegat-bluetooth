#ifndef _VegaT_espcomms_h
#define _VegaT_espcomms_h

SoftwareSerial uart = SoftwareSerial(16,17);

int preset[6];

void calculate_checksum(uint8_t *arr, int size, uint8_t *arr1);
void sendVegaTstatusRequest();
void startbatchmessage();
void stopdeliverymessage();
void resetstopdeliverymessage();
void terminatebatchmessage();
void leakedatarequest();
void sendpresetmodificationrequest();
void batchdatarequest();
void batchdatastoredmessage();
String receivemessageVegaT();

#endif
