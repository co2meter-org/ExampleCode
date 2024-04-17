/*
AN128_ardunio_cozir CO2 Demonstration code 11/29/2017 Runs on Ardunio UNO, MEGA or MEGA2560
  Written by: Marv Kausch 11/22/2016 or Co2meter.com
  Revised 11/29/17 by John Houck
   
  This sketch connects a COZIR sensor and reports readings back to the host computer over USB.
  The value is stored in a global variable 'co2' and can be used for any number of applications.
   
  pin connections:
   
  Arduino________COZIR Sensor
   GND ------------------ 1 (gnd)
   3.3v------------------- 3 (Vcc)  
    11 -------------------- 5 (Rx)
    12 -------------------- 7 (Tx)


Modified by RM on 04/17/24 to work with strings and CM-200 and LEDs
*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 11); // RX, TX pins on Ardunio

// if using a CO2Meter CM-200 Sensor Development Board, set this to 1 if you want the LEDs to flash
// if you're wiring directly to the sensor, set this to 0
#define CM200 1

#if CM200
#define GREEN_LED 4
#define BLUE_LED 5
#define RED_LED 6

uint8_t ind = GREEN_LED;
#endif

// if you want the sensor to stream set this to 1
// if you want to use the sensor in polling mode, set this to 0 and set the delay_ms to desired delay time
#define STREAMING 1
const int delay_ms = 500;

//int co2 = 0;
double multiplier = 1; // 1 for 2% =20000 PPM, 10 for 20% = 200,000 PPM

const uint8_t buff_size = 64;
//uint8_t buff[buff_size];
uint8_t index = 0;

int fill_buffer();  // function prototypes here
int format_output();
double get_co2(char * str);

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n");
  Serial.println("             AN128 Ardunio to Cozir CO2 Sensor - Demonstration code 11/29/2017\n\n");

#if CM200
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
#endif
  
  mySerial.begin(9600); // Start serial communications with sensor

  mySerial.println("M 6"); // send Mode for Z and z outputs
  // "Z xxxxx z xxxxx" (CO2 filtered and unfiltered)

#if STREAMING
  mySerial.println("K 1");  // set streaming mode
#else
  mySerial.println("K 2");  // set streaming mode
#endif
}

void loop() {
  double co2_flt = 0.0;
  double co2_raw = 0.0;
  uint8_t buff[buff_size] = { 0 };

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

  mySerial.flush();
#if STREAMING == 0
  mySerial.println("Z");  // set streaming mode
#endif

  int timeout = 5000;
  while ( mySerial.available() <= 0 && timeout-- > 0) {
    Serial.print(".");
    delay(10);
  }
  Serial.println("");

  delay(10); //delay 10ms to give the Serial buffer some time to fill
  Serial.print("Sensor Response: ");
  index = 0;
  while ( mySerial.available() > 0 ) {
    char tmp = mySerial.read();
    buff[index] = tmp;
    Serial.print((char)tmp);

    if (tmp == '\r')
      break;

    index++;
    if (index >= buff_size) //let's not overflow the buffer
      break;
  }

  Serial.println("");

  char *p = buff;
  char *str;
  
  while ((str = strtok_r(p, " ", &p)) != NULL) {
    if (str[0] == 'Z') {
      str = strtok_r(p, " ", &p);
      co2_flt = get_co2(str);
    }
    if (str[0] == 'z') {
      str = strtok_r(p, " ", &p);
      co2_raw = get_co2(str);
    }
  }

  Serial.println("");
  Serial.print("***** Filtered CO2 PPM: ");
  Serial.print(co2_flt);
  Serial.print("\r\n");
#if STREAMING   // we don't need to print this out if we're not streaming
  Serial.print("***** Raw CO2 PPM: ");
  Serial.print(co2_raw);
  Serial.print("\r\n");
#endif

  delay(delay_ms);
}

double get_co2(char * str) {
  for (int i = 0; i < strlen(str); i++) { //cycle through char array making sure we're all digits
    if (!isDigit(str[i])) {
     str[i] = '\0';
    }
  }

  return atof(str) * multiplier; // this is not great we could crash here if the first character is not a number
}
