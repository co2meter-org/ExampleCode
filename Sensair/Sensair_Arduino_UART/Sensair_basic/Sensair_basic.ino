/*
  Basic Arduino example for K-Series sensor
  Created by Jason Berger
  Co2meter.com  

  Modified by RM
  - 04/17/24 Changing TX line to match CM-200 Sensor Development Board and adding in LEDs from CM-200
*/


#include "SoftwareSerial.h"

SoftwareSerial K_30_Serial(12,11);  //Sets up a virtual serial port
                                    //Using pin 12 for Rx and pin 13 for Tx


// if using a CO2Meter CM-200 Sensor Development Board, set this to 1 if you want the LEDs to flash
// if you're wiring directly to the sensor, set this to 0
#define CM200 1

#if CM200
#define GREEN_LED 4
#define BLUE_LED 5
#define RED_LED 6

uint8_t ind = GREEN_LED;
#endif

const byte readCO2[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};  //Command packet to read Co2 (see app note)
byte response[] = {0,0,0,0,0,0,0};  //create an array to store the response

//multiplier for value. default is 1. set to 3 for K-30 3% and 10 for K-33 ICB
const int valMultiplier = 1;

const int delay_ms = 2000;  // to change the polling interval, update this variable (check sensor data sheet, most cannot be done faster than 2 seconds)

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);         //Opens the main serial port to communicate with the computer
  K_30_Serial.begin(9600);    //Opens the virtual serial port with a baud of 9600

  Serial.println("***** Senseair Basic Arduino Program *****");

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

  sendRequest(readCO2);
  unsigned long valCO2 = getValue(response);
  Serial.print("Co2 ppm = ");
  Serial.println(valCO2);
  delay(delay_ms);
}

void sendRequest(byte packet[]) {
  while(!K_30_Serial.available()) { //keep sending request until we start to get a response
    K_30_Serial.write(readCO2,7);
    delay(50);
  }
  
  int timeout=0;  //set a timeoute counter
  while(K_30_Serial.available() < 7 ) { //Wait to get a 7 byte response
    timeout++;  
    if(timeout > 10) {  //if it takes to long there was probably an error
        while(K_30_Serial.available()) //flush whatever we have
          K_30_Serial.read();
          
        break;                        //exit and try again
     }
     delay(50);
  }
  
  for (int i=0; i < 7; i++)
    response[i] = K_30_Serial.read();
}

unsigned long getValue(byte packet[]) {
  int high = packet[3];                        //high byte for value is 4th byte in packet in the packet
  int low = packet[4];                         //low byte for value is 5th byte in the packet

  unsigned long val = high*256 + low;                //Combine high byte and low byte with this formula to get value
  return val* valMultiplier;
}
