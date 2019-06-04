# K30 1% CO2 Sensor

>image

## Section 1: Operating Your K30 Sensor
The K30 Sensor can communicate via UART, I2C and Analog Output Voltage.  

- ### 1.1 CM-0024 K30 Sensor Development Kit
The CM-0024 Development Kit includes a USB cable wired to the K30 Sensor.  Simply plug the Sensor into a USB Port and run the software.

>image

- ### 1.1.1 Connecting a CM-0024 to Gaslab Software
CO2meter offers Free Gaslab Software that can be downloaded to a Windows 7 ot 10 computer.  
Gaslab allows users to read sensor values, calibrate sensors, log data, create spreadsheets and print graphs.

Download our FREE Gaslab Software from this link
>link

- ### 1.1.2 Connecting a CM-0024 to Raspberry Pi with Python Code

Plug the USB Cable into the USB Port of a Raspberry Pi.
Run the following Python Script.

import serial

import time

ser = serial.Serial("/dev/ttyUSB0",baudrate =9600,timeout = .5)
print "K30 Development Kit to Raspberry Pi3\n"
ser.flushInput()
time.sleep(1)


while True:


    ser.flushInput()
    ser.write("\xFE\x44\x00\x08\x02\x9F\x25")
    time.sleep(1.9)
    resp = ser.read(7)
    high = ord(resp[3])
    low = ord(resp[4])
    co2 = (high*256) + low
    print " CO2 = " +str(co2)
    time.sleep(.1)
