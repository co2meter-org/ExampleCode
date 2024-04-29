#Python progam to run a Cozir Sensor
import serial
import time

ser = serial.Serial("/dev/ttyS0")
print("Python progam to run a Cozir Sensor\n")
ser.write("M 1\r\n".encode()) # set operating mode to polling
# \r\n is CR and LF
ser.flushInput()
time.sleep(1)

while True:
    ser.write("%\r\n".encode())
    resp = ser.read(10)
    resp = resp[:8]

    fltO2 = float(resp[2:])
    print("O2 % = ", fltO2)

    time.sleep(1)
