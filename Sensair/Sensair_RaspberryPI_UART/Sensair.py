#rpi serial connections
#Python app to run a K-30 Sensor
import serial
import time

ser = serial.Serial("/dev/ttyS0",baudrate =9600,timeout = .5)
print("  AN-137: Raspberry Pi3 to K-30 Via UART\n")
ser.flushInput()
time.sleep(1)

while True:
	
    
    ser.flushInput()
    getco2 = bytearray([0xFE,0x44,0x00,0x08,0x02,0x9F,0x25])
    ser.write(getco2)
    time.sleep(.5)
    resp = ser.read(7)
    high = resp[3]
    low = resp[4]
    co2 = (high*256) + low
    print(" CO2 = " +str(co2))
    time.sleep(.1)
