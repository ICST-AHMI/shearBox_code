//https://forums.openmv.io/viewtopic.php?t=194

#define SlaveAddress 0x12
#include <Wire.h>

volatile byte SendByte;
volatile byte RecByte;

//-----------------------------
void CommandToOpenMV(byte Com)
//-----------------------------
{
boolean Checking = true;
  while(Checking)
  {  
    Serial.print(F("Sending Com "));
    Serial.print(Com);
    RecByte = 111;  // OpenMV wait command
    SendByte = Com;
    while(RecByte == 111) delay(1);
    if(RecByte == Com)
    {
      Serial.println(F(" Confirmed"));
      Checking = false;
    }
    else
    {
      Serial.print(F(" RecByte Error = "));
      Serial.println(RecByte);
    }
  } 
}

//----------
void setup()
//----------
{
  Serial.begin(115200);           // start serial for output  
  Serial.println(F("OpenMV to Arduino")); 
  pinMode(13, OUTPUT);
  Wire.begin(SlaveAddress);       // join i2c bus with address SlaveAddress
  Wire.onRequest(requestEvent);   // register event
  Wire.onReceive(receiveEvent);   // register event
  delay(10);
}

//---------
void loop()
//---------
{
  while(true)
  {
    digitalWrite(13, HIGH);
    delay(50);       // delay a bit instead of doing SPI to SRAM
    digitalWrite(13, LOW);
    delay(50);       // delay a bit instead of doing SPI to SRAM   
    CommandToOpenMV(123);
    CommandToOpenMV(124);
    CommandToOpenMV(125);
    CommandToOpenMV(126);
  } 
}

//-----------------
void requestEvent()  
//-----------------
// ISR that executes whenever data is requested by master
{
  Wire.write(SendByte);
  SendByte = 111;
}

//----------------------------
void receiveEvent(int howMany)
//----------------------------
// ISR that executes whenever data is received from master
{
  RecByte = Wire.read(); 
}
