
#include <SoftwareSerial.h>

#define S11_TX 12
#define S11_RX 11
SoftwareSerial s11 = SoftwareSerial(S11_TX, S11_RX);

void setup() {
  // put your setup code here, to run once:
  s11.begin(9600);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte co2Read[] = { 0xfe, 0x04, 0x00, 0x03, 0x00, 0x01, 0xd5, 0xc5 };
  s11.write(co2Read, 8);

  int millisec = 0;
  while(s11.available() <= 0) {
    delay(1);
    millisec++;
    if (millisec > 1500) break;
  }
  delay(50);

  if (s11.available() <= 0) {
    Serial.println("no data available");
    return;
  }

  int s11ResponseSize = s11.available();
  byte s11Response[s11ResponseSize];
  int count = 0;
  while (count < s11ResponseSize) {
    s11Response[count] = s11.read();
    count++;
  }

  int co2 = (s11Response[3] << 8) | s11Response[4];
  Serial.print("CO2 Concentration: ");
  Serial.print(co2);
  Serial.print("\n");
  delay(2000);
}
