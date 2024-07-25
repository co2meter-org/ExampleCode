from smbus3 import SMBus
import time


print("**** Example Code for K30 on I2C ****")


K30_ADDRESS = 0x68
K30_READ_CO2_CMD = [0x22, 0x00, 0x08, 0x2A]
K30_ZERO_CAL_CMD = [0x12, 0x00, 0x67, 0x7C, 0x07, 0xFC]
K30_BACKGROUND_CAL_CMD = [0x12, 0x00, 0x67, 0x7C, 0x06, 0xFB]

DEBUG = 0

bus = SMBus(1)

def validate_checksum(resp, size):
    index = 1
    chksum = 0
    for val in resp:
        if index == size:
            chksum = chksum & 0xFF
            if DEBUG == 1:
                print("Checksum: ")
                print(hex(chksum))
            if chksum == val:
                return True
            else:
                return False
        chksum = chksum + val
        index = index + 1

def get_co2():
    bus.i2c_wr(K30_ADDRESS, K30_READ_CO2_CMD)
    time.sleep(0.05)
    read = bus.i2c_rd(K30_ADDRESS, 4)

    k30_resp = [0,0,0,0]
    index = 0
    for value in read:
        if DEBUG == 1:
            print(hex(value))
        k30_resp[index] = value
        index = index + 1
    
    if validate_checksum(k30_resp, 4):
        co2 = k30_resp[1] * 256 + k30_resp[2]
        return co2
    else:
        return -1

def zero_cal():
    print("*** Calibrating Sensor to 0 ***")

    bus.i2c_wr(K30_ADDRESS, K30_ZERO_CAL_CMD)
    time.sleep(0.05)
    read = bus.i2c_rd(K30_ADDRESS, 2)

    k30_resp = [0,0,0,0]
    index = 0
    for value in read:
        if DEBUG == 1:
            print(hex(value))
        k30_resp[index] = value
        index = index + 1

    if validate_checksum(k30_resp, 2):
        if k30_resp[1] == 0x11:
            print("Zero Calibration Successful")
            return True
        else:
            print("Zero Calibration Failed... Use DEBUG option to see response")
    else:
        print("Could not validate checksum")
        return False

def background_cal():
    print("*** Calibrating Sensor to 400 ***")

    bus.i2c_wr(K30_ADDRESS, K30_BACKGROUND_CAL_CMD)
    time.sleep(0.05)
    read = bus.i2c_rd(K30_ADDRESS, 2)

    k30_resp = [0,0,0,0]
    index = 0
    for value in read:
        if DEBUG == 1:
            print(hex(value))
        k30_resp[index] = value
        index = index + 1

    if validate_checksum(k30_resp, 2):
        if k30_resp[1] == 0x11:
            print("Zero Calibration Successful")
            return True
        else:
            print("Zero Calibration Failed... Use DEBUG option to see response")
    else:
        print("Could not validate checksum")
        return False


while True:
    usrinput = input("Type M for Measurement, Z for Zero Calibration, B for Background Calibration: ")
    if usrinput == 'M':
        print(get_co2())
    elif usrinput == 'Z':
        zero_cal()
    elif usrinput == 'B':
        background_cal()
    else:
        print("Invaid Input")