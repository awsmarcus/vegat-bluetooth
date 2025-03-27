# VegaT Bluetooth Comms

Add bluetooth functionality to the VegaT using an esp32 in order to pull information from the VegaT like transaction data and status to a mobile app via bluetooth .


## Drivers

1. espbluetooth comms
2. VegaTserialcomms

## Current working features 
1. 30 - REQUEST OF STATUS MESSAGE 
2. 44 - START BATCH MESSAGE
3. 45 – STOP DELIVERY MESSAGE
4. 46 - TERMINATE BATCH MESSAGE
5. 53 – LEAK DATA REQUEST MESSAGE
6. 51 - BATCH DATA REQUEST MESSAGE
7. 56 – BATCH DATA STORED MESSAGE
8. 45 – RESET STOP DELIVERY MESSAGE



## Project Status 

1. VegaT serial comms now running , testing different commands
2. Bluetooth initial testing done,works well with serial app on phone .
3. Bluetooth security features including a password system in the works,will be added soon.
4. Raw data that comes from vega t directly sent over bluetooth.
5. Vega T needs to be in remote mode for actions like batch control and transaction data request.
6. Vega T address needs to be 001 for this to work , will be changed in the future.
