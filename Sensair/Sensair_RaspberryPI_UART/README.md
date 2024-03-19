# Setting Up The RaspberryPi (RPI) Project

## Set up your RPI3

1. You will nee3d to set up your Raspberry Pi with Raspian. For more details, follow this link: [https://www.raspberrypi.com/software/](https://www.raspberrypi.com/software/)

2. Connect your Raspberry Pi to your keyboard, mouse, monitor and 5VDC power supply.

3. Power the RPi3 and LCD monitor. In order to access to the attached python files,you will need an internet connection. RPi3 offers a built‐in Wi‐Fi device. On your monitor, find the icon of a terminal. Select the icon, select your Wi‐Fi network, and enter your network password.

4. Verify that you are connected via Wi‐Fi. On your monitor, select the globe icon to open an internet browser. Verify your internet connection by going to https://google.com.

5. Download or clone the repository to the home folder, and navigate to the folder.  You can find instructions on the [ExampleCode main README](https://github.com/co2meter-org/ExampleCode).


## CM-200 Setup
### Switch Settings
Leave the Sensor Configuartion Jumpers as default.  Switch the I2C / UART Switch to the right over UART, and the USB - BLE / ARD - RPI Switch to the right over ARD - RPI.  As pictured below.
![rpi uart switches](./media/cm200-se11-arduino-uart.jpg)

### Raspberry Pi
CO2Meter recommends, for Raspberry Pi Zero, purchasing and soldering these [header pins](https://www.amazon.com/gp/product/B084Q4W1PW/ref=ox_sc_act_title_1?smid=A12R7FMO56ISX4&psc=1) to be able to stack on top of the CM-200
![rpi on cm200](./media/cm200-rpi.jpg)

## Wiring without a CM-200

![Rx -> Rx; Tx -> Tx](./media/wiring.png)

## Create and run your RPI3-K30 Project
   1. Select Menu -> Programming -> Geany

   2. Select File -> Open -> pi -> AN137 -> K30

   3. Verify that you see:
   ![Alt text](./media/geany.png)

   4. Select Build -> compile

   5. Select Build -> execute
