# CAN Bus & I-Bus Nachrichten Codes


## CAN Bus 

### RPM
L2 = RPM LSB
L3 = RPM MSB from 0.00f to 175.00f
unsigned char message1[8] = {0x05, 0x62, 0xFF, RPMSendVal, 0x65, 0x12, 0, 62};
CAN.sendMsgBuf(0x316, 0, 8, message1);

### DME 4
L0 = 0x10=EML, 0x08=Cruise Control, 0x02=Motor Light
L1 = 0x01=Traction Control
L1 = ? Probably L/100km -> Maybe the Change of Rate is needed to calculate in the cluster
L3 = 0x08=Overheat Light, 0x02=Oillight
L4 = ? Probably Oiltemp -> not as analog in the cluster, so ignored for now
L5 = Charging Light 0x00=off, 0x01=on

Coolant Temperature
Calculation, maxTemp=260.00f, minTemp=50.00f
Temp Scaling to Float based on temperaturerange from 50 to 130 Degree Celsius


## K-Bus-Data

### For Lightbyte1
0x04=Indicator Highbeam
0x08=Indicator Foglight rear
0x10=Indicator Foglight front
0x14=Fogrear+Highbeam
0x20=Indicator Left
0x24=Left+Highbeam
0x28=Left+Fogrear
0x30=Left+Fogfront
0x34=Left+Fogfront+Highbeam
0x38=Left+Fogfront+Fogrear
0x40=Indicator Right
0x44=Right+Highbeam
0x50=Right+Fogfront
0x54=Right+Fogfront+Highbeam
0x58=Right+Fogfront+Fogrear
0x60=Both Indicators
0x64=Both+Highbeam
0x70=Both+Fogfront
0x74=Both+Fogrfront+Highbeam
0x78=Both+Fogfront+Fogrear

### For Lightbyte2
0x30=Frontlights
