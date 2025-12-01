#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

const int SPI_CS_PIN = 9;
MCP2515 CAN(SPI_CS_PIN); 

#define kbus Serial2

#define SPEED_PIN 46

int pinABS = 34;
int pinParkingpbrake = 36;
int pinClusterlight = 38;

int hibeam = 0; 
int pbrk = 0; 
int tc = 0; 
int turnleft = 0; 
int turnright = 0; 
int hazard = 0; 
int oilwarn = 0;
int batt = 0;
int absBlink = 0;

int MaxRPM = 7000;
float RPMSendVal = 0.00f;
int SpeedSendVal = 50;
float TempSendVal = 50.00f;

byte LightByte1 = 0x00;
byte LightByte2 = 0x00;

byte DME4_Load0 = 0x00;
byte DME4_Load3 = 0x00;
byte DME4_Load5 = 0x00;
byte DME6_Load1 = 0x00;
byte AT_Gear = 0x00;

int Speed = 0;
int RPM = 0;
int Temp = 0;
int fuelpercentage = 0;
int oilpress = 0;    
String checkEngine_ETS = "0";
String blinkerleft;
String blinkerright;   
String cruise;
String parkingbreak;
String oil_warn;
String batWarning = "FALSE";
String lights; 
int turnLeft = 0;
int turnRight = 0;
int absWarning = 0;   
int dscWarning = 0;
int dscSwitch = 0;
String checkEngine_PCARS = "0";
String Highbeam = "False";
int pcars_mcarflags = 0;
int acc_lightstage = 0;
int acc_flashlight =  0;
int handbrake = 0;
int turnleft_fs = 0;
int turnright_fs = 0;
String cruise_fs;
String engine_fs;
String lights_fs;
int parkingbreak_beam = 0;
int turnleft_beam = 0;
int turnright_beam = 0;
int foglight_beam = 0;
int oillight_beam = 0;
int abslight_beam = 0;
int watertemp_beam = 0;
int lowhighbeam_beam = 0;
int highbeam_beam = 0;
int tclight_beam = 0;

String gear;
int showLights = 0;
String Game = "ETS2";

//####################################################

int inputIngameoption = 30;
int inputHardwareoption = 31;
int inputAlwaysonoption = 32;
int inputHardwareswitch = 33;

class SHCustomProtocol {
private:

public:

  void setup() {

  pinMode(inputIngameoption, INPUT_PULLUP);
  pinMode(inputHardwareoption, INPUT_PULLUP);
  pinMode(inputAlwaysonoption, INPUT_PULLUP);
  pinMode(inputHardwareswitch, INPUT_PULLUP);
  
  pinMode(pinABS, OUTPUT);
  pinMode(pinParkingpbrake, OUTPUT);
  pinMode(pinClusterlight, OUTPUT);

  digitalWrite(pinABS, HIGH);
  digitalWrite(pinParkingpbrake, HIGH);
  digitalWrite(pinClusterlight, HIGH);
    
    pinMode(SPEED_PIN, OUTPUT);

    kbus.begin(9600, SERIAL_8E1);

     CAN.reset();
     CAN.setBitrate(CAN_500KBPS, MCP_8MHZ);
     CAN.setNormalMode();
  }

  // Called when new data is coming from computer
  void read() {
    // EXAMPLE 1 - read the whole message and sent it back to simhub as debug message
    // Protocol formula can be set in simhub to anything, it will just echo it
    // -------------------------------------------------------
      Speed = FlowSerialReadStringUntil(';').toInt();
      RPM = FlowSerialReadStringUntil(';').toInt();
      Temp = FlowSerialReadStringUntil(';').toInt();
      fuelpercentage = FlowSerialReadStringUntil(';').toInt();
      oilpress = FlowSerialReadStringUntil(';').toInt();
      checkEngine_ETS = FlowSerialReadStringUntil(';');
      blinkerright = FlowSerialReadStringUntil(';');
      blinkerleft = FlowSerialReadStringUntil(';');
      cruise = FlowSerialReadStringUntil(';');
      parkingbreak = FlowSerialReadStringUntil(';');
      oil_warn = FlowSerialReadStringUntil(';');
      batWarning = FlowSerialReadStringUntil(';');
      lights = FlowSerialReadStringUntil(';');
      turnLeft = FlowSerialReadStringUntil(';').toInt();
      turnRight = FlowSerialReadStringUntil(';').toInt();
      absWarning = FlowSerialReadStringUntil(';').toInt();
      dscWarning = FlowSerialReadStringUntil(';').toInt();
      dscSwitch = FlowSerialReadStringUntil(';').toInt();
      checkEngine_PCARS = FlowSerialReadStringUntil(';');
      Highbeam = FlowSerialReadStringUntil(';');
      pcars_mcarflags = FlowSerialReadStringUntil(';').toInt();
      acc_lightstage = FlowSerialReadStringUntil(';').toInt();
      acc_flashlight =  FlowSerialReadStringUntil(';').toInt();
      handbrake =  FlowSerialReadStringUntil(';').toInt();
      turnleft_fs =  FlowSerialReadStringUntil(';').toInt();
      turnright_fs =  FlowSerialReadStringUntil(';').toInt();
      cruise_fs = FlowSerialReadStringUntil(';');
      engine_fs = FlowSerialReadStringUntil(';');
      lights_fs = FlowSerialReadStringUntil(';');
      gear = FlowSerialReadStringUntil(';');
      showLights = FlowSerialReadStringUntil(';').toInt();
      parkingbreak_beam = FlowSerialReadStringUntil(';').toInt();
      turnleft_beam = FlowSerialReadStringUntil(';').toInt();
      turnright_beam = FlowSerialReadStringUntil(';').toInt();
      foglight_beam = FlowSerialReadStringUntil(';').toInt();
      oillight_beam = FlowSerialReadStringUntil(';').toInt();
      abslight_beam = FlowSerialReadStringUntil(';').toInt();
      watertemp_beam = FlowSerialReadStringUntil(';').toInt();
      lowhighbeam_beam = FlowSerialReadStringUntil(';').toInt();
      highbeam_beam = FlowSerialReadStringUntil(';').toInt();
      tclight_beam = FlowSerialReadStringUntil(';').toInt();
      Game = FlowSerialReadStringUntil('\n');
  
    /*
    // -------------------------------------------------------
    // EXAMPLE 2 - reads speed and gear from the message
    // Protocol formula must be set in simhub to
    // format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
    // -------------------------------------------------------

    int speed = FlowSerialReadStringUntil(';').toInt();
    String gear = FlowSerialReadStringUntil('\n');

    FlowSerialDebugPrintLn("Speed : " + String(speed));
    FlowSerialDebugPrintLn("Gear : " + gear);
    */
  }

  // Called once per arduino loop, timing can't be predicted, 
  // but it's called between each command sent to the arduino
 
  void loop() {
  
// ##############
// START GAMEDATA
// ##############


//#################################################### Assetto Corsa 
if(Game.equalsIgnoreCase("AssettoCorsa")) {

  
  DME4_Load3 = 0x00;
  DME4_Load5 = 0x00;
  DME4_Load0 = 0x00;

  
if (gear.equalsIgnoreCase("N")) {
  DME4_Load0 = 0x10;
  DME4_Load0 = 0x08;
} else {
  DME4_Load0 = 0x00;
}

  
}


//###################################################  Euro Truck Simulator 2
if(Game.equalsIgnoreCase("ETS2") || Game.equalsIgnoreCase("ATS")) {

 if(lights.equalsIgnoreCase("true")) {
  LightByte2 = 0x30;
  LightByte2 = 0x14;
} else {
  LightByte2 = 0x00;
}

if(digitalRead(inputIngameoption) == LOW){
if(lights.equalsIgnoreCase("true")) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if (batWarning.equalsIgnoreCase("False")) {
  DME4_Load5 = 0x00;
} else if (batWarning.equalsIgnoreCase("0")) {
  DME4_Load5 = 0x00;
} else {
  DME4_Load5 = 0x01;     
}

if (oilpress <= 1) {
  DME4_Load3 = 0x02;
} else if(Temp >= 100) {
  DME4_Load3 = 0x08;
} else {
  DME4_Load3 = 0x00;
}

if (checkEngine_ETS > "0.2") {
  DME4_Load0 = 0x02;
} else if (cruise.equalsIgnoreCase("True")) {
  DME4_Load0 = 0x08;
} else {
  DME4_Load0 = 0x00;
}

if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x18;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x04;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x58;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x38;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("False")) {
  LightByte1 = 0x78;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("False") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x24;
} else if(blinkerleft.equalsIgnoreCase("False") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x44;
} else if(blinkerleft.equalsIgnoreCase("True") && blinkerright.equalsIgnoreCase("True") && Highbeam.equalsIgnoreCase("True")) {
  LightByte1 = 0x70;
}

if(parkingbreak.equalsIgnoreCase("true")) {
  digitalWrite(pinParkingpbrake, LOW);  
}
else {
  digitalWrite(pinParkingpbrake, HIGH); 
}

}
//#################################################### No Game Data
if(Game.equalsIgnoreCase("ETS2") || Game.equalsIgnoreCase("ATS") || Game.equalsIgnoreCase("AssettoCorsa") || Game.equalsIgnoreCase("pCars") || Game.equalsIgnoreCase("FH5") || Game.equalsIgnoreCase("FernbusSimulator") || Game.equalsIgnoreCase("BeamNgDrive")) {
  
} else {
  digitalWrite(pinParkingpbrake, HIGH);
  LightByte1 = 0x00;
  LightByte2 = 0x00;
  DME4_Load0 = 0x00;
  DME4_Load3 = 0x00;
  DME4_Load5 = 0x00;
}

//#################################################### GameData

if(digitalRead(inputAlwaysonoption) == LOW) {
digitalWrite(pinClusterlight, LOW);  
}

if(digitalRead(inputHardwareoption) == LOW){
if(digitalRead(inputHardwareswitch) == LOW) {
digitalWrite(pinClusterlight, LOW);  
}
else {
digitalWrite(pinClusterlight, HIGH);
}
}

if ((dscWarning == 1) && (dscSwitch == 1)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 1) && (dscSwitch == 0)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 0) && (dscSwitch == 1)) {
DME6_Load1 = 0x01;
}
else if ((dscWarning == 0) && (dscSwitch == 0)) {
DME6_Load1 = 0x00;
}

if (absWarning == 0) {
digitalWrite(pinABS, HIGH);
}
else {
digitalWrite(pinABS, LOW);
}
//#################################################### Ende GAMEDATA
Speedometer();

  if(RPM > MaxRPM) { RPM = MaxRPM; }
 
  RPMSendVal = map(RPM, 0, 7000, 0, 175.00f); 

  CanSend(0x316, 0x05, 0x62, 0xFF, RPMSendVal, 0x65, 0x12, 0, 62);

  CanSend(0x545, DME4_Load0, 0x00, 0x00, DME4_Load3, 0x00, DME4_Load5, 0x00, 0x00);

  
  if(Temp >= 130) {
    Temp = 125;
  }
  if(Temp <= 50) {
    Temp = 80;
  }
  TempSendVal = map(Temp, 50, 130, 50.00f, 260.00f);
  CanSend(0x329, 0x00, TempSendVal, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);  

  CanSend(0x153, 0x00, DME6_Load1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
  

  byte mes1[] = {0xD0, 0x08, 0xBF, 0x5B, LightByte1, 0x00, 0x00, LightByte2, 0x00, 0x58, 0x00};
  sendKbus(mes1);

  
  }

  void idle() {
  }

void CanSend(short address, byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h) {
    struct can_frame frame;
    frame.can_id  = address;
    frame.can_dlc = 8;
    frame.data[0] = a;
    frame.data[1] = b;
    frame.data[2] = c;
    frame.data[3] = d;
    frame.data[4] = e;
    frame.data[5] = f;
    frame.data[6] = g;
    frame.data[7] = h;
    CAN.sendMessage(&frame);
}

void sendKbus(byte *data)
{
  int end_i = data[1]+2 ;
  data[end_i-1] = iso_checksum(data, end_i-1);
  kbus.write(data, end_i + 1);
}

void Speedometer()
{
  if(Speed == 0)
  {
    noTone(SPEED_PIN); 
  }else{
    SpeedSendVal = map(Speed, 0, 250, 0, 1680);
    tone(SPEED_PIN, SpeedSendVal); 
  }

}


byte iso_checksum(byte *data, byte len)
{
  byte crc=0;
  for(byte i=0; i<len; i++)
  {    
    crc=crc^data[i];
  }
  return crc;
}

};

#endif