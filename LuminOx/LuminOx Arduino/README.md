### Interface Arduino with GSS Sensors
- CozIR-A 2,000 [GC-0010](https://www.co2meter.com/collections/sensors/products/cozir-2000-ppm-co2-sensor)
- CozIR-A 5,000 [GC-0011](https://www.co2meter.com/collections/sensors/products/cozir-ambient-5000-ppm-co2-sensor)
- CozIR-A 10,000 [GC-0012](https://www.co2meter.com/collections/sensors/products/cozir-ambient-10000-ppm-co2-sensor)
- CozIR-A 2,000RHT [GC-0020](https://www.co2meter.com/collections/sensors/products/cozir-co2-temperature-humidity-sensor)
- CozIR-A 10,000RHT [GC-0022](https://www.co2meter.com/collections/sensors/products/cozir-10000-ppm-co2-temperature-humidity-sensor)
- GC-0006 [GC-0006](https://www.co2meter.com/collections/sensors/products/cozir-wrv-20-percent-co2-sensor)
- GC-0007 [GC-0007](https://www.co2meter.com/collections/sensors/products/cozir-wr-60-percent-co2-sensor)
- GC-0015 [GC-0015](https://www.co2meter.com/collections/sensors/products/cozir-wr-5-percent-co2-sensor)
- GC-0016 [GC-0016](https://www.co2meter.com/collections/sensors/products/cozir-100-percent-co2-sensor)
- GC-0017 [GC-0017](https://www.co2meter.com/collections/sensors/products/sprintir-wr-20-pct-co2-sensor)
- GC-0018 [GC-0018](https://www.co2meter.com/collections/sensors/products/sprintir-100-percent-co2-sensor)
- Cozir-LP [GC-0027](https://www.co2meter.com/collections/sensors/products/cozir-lp-ambient-air-co2-sensor)
- Cozir-LP2 [GC-0034](https://www.co2meter.com/collections/sensors/products/copy-of-cozir-lp-miniature-5-000ppm-co2-sensor)
- SprintIR-6S-5 [GC-0028](https://www.co2meter.com/collections/sensors/products/sprintir6s-5-co2-smart-sensor)
- SprintIR-6S-20 [GC-0029](https://www.co2meter.com/collections/sensors/products/sprintir6s-20-co2-smart-sensor)
- SprintIR-6S-100 [GC-0030](https://www.co2meter.com/collections/sensors/products/sprintir6s-100-co2-smart-sensor)
- ExplorIR-M-5 [GC-0024](https://www.co2meter.com/collections/sensors/products/minir-co2-sensor)
- ExplorIR-M-20 [GC-0026](https://www.co2meter.com/collections/sensors/products/explorir-20-co2-smart-led-sensor)
- ExplorIR-M-100 [GC-0025](https://www.co2meter.com/collections/sensors/products/explorir-100-pct-co2-sensor)


## Creating an Arduino Project

1. Wire up your device as shown:
![Rx -> Rx; Tx -> Tx](wiring.png)

2. Check that your Arduino is connected to a USB port and the on‐board LED indicates power is on.

3. Download this git repo or click this link to download the *.ino file: http://co2meters.com/Documentation/AppNotes/AN128-COZIRWR-arduino-uart.zip

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
