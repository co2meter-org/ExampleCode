from smbus3 import SMBus
import time


print("**** Example Code for K30 on I2C ****")


K30_ADDRESS = 0x68
K30_READ_CO2_CMD = [0x22, 0x00, 0x08, 0x2A]

DEBUG = 0
# setting the delay to 2 second, change if you want it faster or slower
DELAY = 2

bus = SMBus(1)

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

    co2 = k30_resp[1] * 256 + k30_resp[2]
    return co2

while True:
    try:
        co2 = get_co2()
        print(co2)
    except:
        print("error getting i2c data from K30")
    time.sleep(DELAY)

