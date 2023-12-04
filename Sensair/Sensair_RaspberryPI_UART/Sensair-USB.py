#rpi serial connections
#Python app to run a K30 Sensor Development Kit 01/17/2017 JTH
import serial
import time

ser = serial.Serial("/dev/ttyUSB0",baudrate =9600,timeout = .5)
print "K30 Development Kit to Raspberry Pi3\n"
ser.flushInput()
time.sleep(1)


while True:
    print "              CO2Meter.com\n"
    time.sleep(.1)
    print "                CM-0024\n"
    time.sleep(.5)
    print "\n"
    
    ser.flushInput()
    ser.write("\xFE\x44\x00\x08\x02\x9F\x25")
    time.sleep(1.9)
    resp = ser.read(7)
    high = ord(resp[3])
    low = ord(resp[4])
    co2 = (high*256) + low
    print " CO2 = " +str(co2)
    time.sleep(.1)
