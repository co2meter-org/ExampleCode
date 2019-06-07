# K30 1% CO2 Sensor

>image

## Section 1: Operating Your K30 Sensor
The K30 Sensor can be purchased as a bare sensor or as a CM-0024 Sensor Development Kit.  
As a bare Sensor, the K30  can communicate via UART, I2C and Analog Output Voltage.  
The CM-0024 K30 Sensor Development Kit consists of a K30 Sensor pre-wired to a USB cable with mating connectors.

- ### 1.1 CM-0024 K30 Sensor Development Kit
The CM-0024 K30 Sensor Development Kit is the fastest and easiest way to start using your K30 Sensor.  It includes a USB cable to plug the Sensor into a computer or Raspberry Pi.

>image

- ### 1.1.1 CM-0024 Development Kit with Gaslab Software
CO2meter offers Free Gaslab Software that can be downloaded to a Windows 7 ot 10 computer.  Simply plug the USB Cable into your Gaslab Computer to read sensor values, calibrate sensors, log data, create spreadsheets and print graphs.

Download our FREE Gaslab Software from this link
>link

- ### 1.1.2 CM-0024 Development Kit to Raspberry Pi with Python
The CM-0024 Development Kit is compatible with many Raspberry Pi computers.

Plug in the USB Cable into the Raspberry Pi and run the following Python Script.  
No wiring, no soldering, no mistakes... just Plug & Play.


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


- ### 1.2 K30 Sensor UART wired to Raspberry Pi GPIO Pins.
The K30 Sensor UART connections can be wired to Raspberry Pi GPIO Pins.

>image K30 UART GPIO RPi 

- ### 1.2.1 Configuring the Raspberry Pi for UART on GPIO Pins.
Perform the following instructions to activate UART on GPIO Pins.

>instructions to configure RPi UART/ enable GPIO pins

Run the following Python code:

>UART GPIO python code
