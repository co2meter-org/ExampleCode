
#include <Wire.h>

char FIND_ADDRESS = 'F';
char READ_CO2 = 'R';
byte address = 0x68;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(10000);
  Serial.begin(115200);
  Serial.println("Type F to find all devices on I2C bus and type R to read CO2 from S-11");
}

void sendDataAndReadToAddress(byte reg, byte address, int bufferSize, int readCount) {
  Wire.beginTransmission(address);  
  for (int k = 0; k < bufferSize; k++) {
    Wire.write(reg);    
  }
  Wire.endTransmission(false);  

  delay(20);

  Wire.requestFrom(address, readCount);

  delay(10);
  int nBytes = Wire.available();
  byte buff[nBytes];

  int i = 0;
  while (Wire.peek() != -1) {
    buff[i] = Wire.read();
    Serial.print(buff[i],HEX);
    Serial.print(" ");
    i++;
  }
  //Serial.write(buff, nBytes);
  Serial.print('\n');

  int co2 = (buff[0] << 8) | buff[1];
  Serial.print("CO2 Concentration: ");
  Serial.print(co2);
  Serial.print("\n");
}

void getAllAddress() {
  //Serial.println("Looking for addresses");
  byte error, address;
  for (address = 1; address < 128; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    delay(5);

    if (error == 0) {
      Serial.print(address, HEX);
      Serial.print(" ");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) { }
  //Delay 10ms to ensure we get the whole message
  delay(10);

  int serialBufferSize = Serial.available();
  byte buff[serialBufferSize];

  int i = 0;
  while (Serial.peek() != -1 && i < serialBufferSize) {
    buff[i] = (byte)Serial.read();
    i++;
  }
  char command = (char)buff[0];
  if (command == FIND_ADDRESS) {
    getAllAddress();
  } else if (command == READ_CO2) {
    //The LSB nibble of the second byte contains the number of data bytes being read
    //Add 2 for the Command byte and Checksum
    int bufferSize = 1;
    int readCount = 2;
    sendDataAndReadToAddress(0x06, address, bufferSize, readCount);
  } else {
    Serial.println("Invalid Command... Type F to find all devices on I2C bus and type R to read CO2 from S-11");
  }
}