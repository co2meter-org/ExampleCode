
#include <SoftwareSerial.h>

/*NOTE:
 * This Arduino program is assuming the S11 is in continuous mode.  For more info check out Senseair's Sunrise GitHub repository here: https://github.com/Senseair-AB/Sunrise-Examples---Arduino
 * or 
 */
// if using a CO2Meter CM-200 Sensor Development Board, set this to 1 if you want the LEDs to flash
// if you're wiring directly to the sensor, set this to 0
#define CM200 1

#if CM200
#define GREEN_LED 4
#define BLUE_LED 5
#define RED_LED 6

uint8_t ind = GREEN_LED;
#endif

#define S11_TX 12
#define S11_RX 11
SoftwareSerial s11 = SoftwareSerial(S11_TX, S11_RX);

const int delay_ms = 2000;  // to change the polling interval, update this variable (check sensor data sheet, most cannot be done faster than 2 seconds)

void setup() {
  // put your setup code here, to run once:
  s11.begin(9600);
  Serial.begin(9600);

  Serial.println("***** Senseair Sunrise SE-11 Arduino Program *****");

#if CM200
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
#if CM200
  // if using a CM-200 we can cycle through the LEDs to high and low so we can see that we're in the loop
  if (digitalRead(ind) == HIGH)
    digitalWrite(ind, LOW);
  else
    digitalWrite(ind, HIGH);

  ind++;
  if (ind > RED_LED)
    ind = GREEN_LED;
#endif
  
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
  delay(delay_ms);
}
