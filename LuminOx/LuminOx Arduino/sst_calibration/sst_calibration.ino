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
#include <EEPROM.h>

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

#define CAL_DATA_ADDRESS  0

const int delay_ms = 500;

const uint8_t buff_size = 64;
uint8_t index = 0;
float f_cal_offset = 0.0;

int fill_buffer();  // function prototypes here
int format_output();
double parse_response(char * str);

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

  mySerial.println("M 1");  // set polling mode
  delay(100);
  while (mySerial.available()) //flush out the response from M
    mySerial.read();

  f_cal_offset = get_calibration();
}

void loop() {
  double o2_pct = 0.0;
  char buff[buff_size] = { 0 };

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

  Serial.println("***");
  Serial.println("***");
  Serial.println("***");
  Serial.println("Send M for Measurement and C followed by a number for Calibration");
  Serial.println("Ex: C 21.0 to calibrate measurement to 21.0%");

  while (Serial.available() <= 0); // wait for user input

  delay(50);  //give some time to get all of the bytes
  index = 0;
  while (Serial.available() > 0) {
    //Serial.println((char)Serial.read());
    buff[index] = (char)Serial.read();
    Serial.print(buff[index]);
    if (buff[index] == '\r')
      break;

    index++;
  }

  if (buff[0] == 'M') {
    // take measurement, read, offset with calibration, display
    o2_pct = take_measurement();
    o2_pct = o2_pct * f_cal_offset;
  } else if (buff[0] == 'C') {
    // take measurement, calculate calibration offset, display
    o2_pct = take_measurement();

    char *p = buff;
    char *str;
    str = strtok_r(p, " ", &p);
    str = strtok_r(p, " ", NULL);
    Serial.println(str);
    f_cal_offset = parse_response(str);

    Serial.print("Calibrating to: ");
    Serial.print(f_cal_offset);
    Serial.println("");
    Serial.println("");

    f_cal_offset = f_cal_offset / o2_pct;
    save_calibration(f_cal_offset);
    o2_pct = o2_pct * f_cal_offset;
  } else {
    Serial.println("Invalid Command");
    return;
  }

  Serial.println("");
  Serial.print("***** Calibrated Sensor O2 Percent: ");
  Serial.print(o2_pct);
  Serial.print("\r\n");

  delay(delay_ms);
}

float get_calibration() {
  float cal_offset = 0.0;
  EEPROM.get(CAL_DATA_ADDRESS, cal_offset);
  return cal_offset;
}

void save_calibration(float cal_offset) {
  EEPROM.put(CAL_DATA_ADDRESS, cal_offset);
}

double take_measurement() {
  float o2_pct = 0.0;
  uint8_t buff[buff_size] = { 0 };

  mySerial.flush();
  mySerial.println("%");  // set streaming mode

  int timeout = 5000;
  while ( mySerial.available() <= 0 && timeout-- > 0) {
    Serial.print(".");
    delay(10);
  }
  Serial.println("");

  delay(50); //delay 50ms to give the Serial buffer some time to fill
  Serial.print("Sensor Response: ");
  index = 0;
  while ( mySerial.available() > 0 ) {
    char tmp = mySerial.read();
    buff[index] = tmp;
    Serial.print((char)tmp);

    if (tmp == '\n')
      break;

    index++;
    if (index >= buff_size) { //let's not overflow the buffer
      Serial.println("Overflowed buffer... Bail!");
      break;
    }
  }

  Serial.println("");

  char *p = buff;
  char *str;
  
  while ((str = strtok_r(p, " ", &p)) != NULL) {
    if (str[0] == '%') {
      str = strtok_r(p, " ", &p);
      o2_pct = parse_response(str);
    }
  }

  Serial.println("");
  Serial.print("***** Raw Sensor O2 Percent: ");
  Serial.print(o2_pct);
  Serial.print("\r\n");

  return o2_pct;
}


double parse_response(char * str) {
  for (int i = 0; i < strlen(str); i++) { //cycle through char array making sure we're all digits
    if (!isDigit(str[i]) && str[i] != '+' && str[i] != '.') {
     str[i] = '\0';
    }
  }

  return atof(str); // this is not great we could crash here if the first character is not a number
}
