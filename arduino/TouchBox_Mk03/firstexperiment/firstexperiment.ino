void setup()
{
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop()
{
  long t0, t;

  int aval = 0;
  
  t0 = micros();
  for(int i=0; i<1000; i++) {
    aval = analogRead(A0);
  }
  t = micros()-t0;  // calculate elapsed time

  Serial.print("Time per sample: ");
  Serial.println((float)t/1000);
  Serial.print("Frequency: ");
  Serial.println((float)1000*1000000/t);
  Serial.println(aval);
  Serial.println();
  delay(2000);
}

void TX(int value, byte channel)
{
  byte LSB, MSB;
  int tmpVal;
  
  LSB = 0;
  //shift the channel number three places to the left
  // B100000000 | B0000cccc -> B1cccc000
  MSB = B10000000 | (channel << 3); 
    
  // take the top 3 bits only (vvv0000000)
  tmpVal = value & 896;
  // and shift it 7 bits to the right (00000vvv)
  tmpVal = tmpVal >> 7;
  // and add it to the MSB 
  MSB = MSB | tmpVal; // B1cccc000 | B00000vvv -> B1ccccvvv
  
  // then store only the lower 7 bits of the value
  LSB = value & B01111111; // Bvvvvvvvvvv & B0001111111 -> B0vvvvvvv

  Serial.write(MSB);
  Serial.write(LSB);
}
