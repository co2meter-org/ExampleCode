## Creating an Arduino Project

1. Wire up your device as shown:
![Rx -> Rx; Tx -> Tx](wiring.png)

2. Check that your Arduino is connected to a USB port and the on‐board LED indicates power is on.

3. Download this git repo or click this link to download the *.ino file: http://www.co2meters.com/Documentation/AppNotes/AN102-K30-Sensor-Arduino-I2C.zip

4. Save the file where you will remember it (if you want to use it later).

5. Double click the file or right click and press 'Open in Arduino IDE' to open the project.

6. You may see a prompt that says: 
![Alt text](move_sketch.png)
If you do, press 'OK.'

7. Select your board in the top left if it was not done for you. If you cannot select your Arduino board, ensure it is plugged into your computer.
![Alt text](arduino_ide.png)

8. Press the checkmark in the top right to compile the code.

9. Press the arrow to send it to your device.

10. To verify it was flashed, use Tools->Serial Monitor and ensure the device is sending you messages
