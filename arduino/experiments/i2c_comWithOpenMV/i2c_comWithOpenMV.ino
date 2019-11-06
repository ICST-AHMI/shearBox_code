//###################################################################################################
//# Arduino Code
//###################################################################################################

// found on https://github.com/openmv/openmv/blob/master/scripts/examples/02-Board-Control/arduino_i2c_slave.py#L65

#include <Wire.h>
#define BAUD_RATE 19200
#define CHAR_BUF 128

void setup() {
  Serial.begin(BAUD_RATE);
  Wire.begin();
  delay(1000); // Give the OpenMV Cam time to bootup.
}

void loop() {
  int32_t temp = 0;
  char buff[CHAR_BUF] = {0};

  Wire.requestFrom(0x12, 2);
  if(Wire.available() == 2) { // got length?

    temp = Wire.read() | (Wire.read() << 8);
    //delay(1); // Give some setup time...

    Wire.requestFrom(0x12, temp);
    if(Wire.available() == temp) { // got full message?

      temp = 0;
      while(Wire.available()) buff[temp++] = Wire.read();

      // the structure of the buffer is: <id>|<centroidX>|<centroidY>|<pixels>
      String str = String(buff);
      String index = str.substring(0, str.indexOf("|"));
      str = str.substring(str.indexOf("|") + 1, str.length());
      String centroidX = str.substring(0, str.indexOf("|"));
      str = str.substring(str.indexOf("|") + 1, str.length());
      String centroidY = str.substring(0, str.indexOf("|"));
      String pixels = str.substring(str.indexOf("|") + 1, str.length());

      int i = idx.toInt();
      if(i < 3){ // we can only transfere 
        
      }
      int cx = centroidX.toInt();
      
      if(
      Serial.print(idx);
      Serial.print("-");
      Serial.print(cx);
      Serial.print("-");
      Serial.print(cy);
      Serial.print("-");
      Serial.println(pix);

    } else {
      while(Wire.available()) Wire.read(); // Toss garbage bytes.
    }
  } else {
    while(Wire.available()) Wire.read(); // Toss garbage bytes.
  }

  //delay(1); // Don't loop to quickly.
}
