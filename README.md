# xPLBee Board

*Arduino IDE compatible board with XBee® module*

---
Copyright © 2015-2017 epsilonRT, All rights reserved.

<a href="http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html">
  <img src="https://raw.githubusercontent.com/epsilonrt/gxPL/master/doc/images/osi.png" alt="osi.png" align="right" valign="top">
</a>

The xPLBee is a microcontroller board based on the ATMEGA1284p compatible with the Arduino IDE:

![xPLBee Board](https://github.com/epsilonrt/xplbee/raw/master/doc/images/xplbee-board-3d.png)

* 128KB FLASH
* 16KB of RAM
* 4KB of EEPROM
* 2 8-bit and 2-bit 16-bit timers (6 PWM channels)
* 8 channels ADC
* 2 USART
* an I²C bus (with pull-up resistors disconnectable).
* a SPI bus (master or slave)
* a JTAG interface (with HE10 connector)
* a quartz 16MHz
* a 32k768 quartz for the RTC timer
* an header for XBee® module with 3 LEDs, 1 pushbutton and 1 extension connector.
* a mini USB connector connected to an FTDI circuit supporting a serial link. This serial link has TXD/RXD/CTS/RTS/DTR signals that can be connected to the microcontroller (PD0/PD1/PD4/PD5/RESET). For the use of an Arduino-compatible bootloader, the TXD, RXD and DTR signals are used.
* a switched-mode power supply that accepts a voltage between 7 and 23V, in the absence of an external input voltage, the power supplied by the mini USB connector is used (switching is automatic). Regardless of the source of the power supply, the supply voltage can be changed: either 5V or 3.3V (essential position for XBee modules).
* a led connected to PB7 (Arduino Pin 7)
* a push button RESET

## Hardware

The pinout is as follows:

![pinout](https://github.com/epsilonrt/xplbee/raw/master/doc/images/atmega1284-pinout.png)

## How to install

#### Boards Manager Installation

This installation method requires Arduino IDE version 1.6.5 or greater.

* Find the desired xPLBee release on the [xPLBee Release page](https://github.com/epsilonrt/xplbee/releases)  
* Use the "Copy link address" feature of your browser to copy the URL of the associated **.json** file  
* Open the Arduino IDE  
* Open the **File > Preferences** menu item  
* Paste the following URL in **Additional Boards Manager URLs**  
    * Separate the URLs using a comma ( **,** ) if you have more than one URL  
* Open the **Tools > Board > Boards Manager...** menu item  
* Wait for the platform indexes to finish downloading  
* Scroll down until you see the **xPLBee** entry and click on it  
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

#### Manual Installation

* Find the desired xPLBee release on the [xPLBee Release page](https://github.com/epsilonrt/xplbee/releases)  
* Click on the `xplbee.tar.gz` file. Extract the archive file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
* Open Arduino IDE, and a new category in the boards menu called "xPLBee" will show up.

## IDE Board options

### BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader". Below is a table that shows the available BOD options:
<br/>

| ATmega1284 | Atmega644 | ATmega324 | ATmega164 | ATmega32 | ATmega16 | ATmega8535 |
|------------|-----------|-----------|-----------|----------|----------|------------|
| 4.3v       | 4.3v      | 4.3v      | 4.3v      | 4.0v     | 4.0v     | 4.0v       |
| 2.7v       | 2.7v      | 2.7v      | 2.7v      | 2.7v     | 2.7v     | 2.7v       |
| 1.8v       | 1.8v      | 1.8v      | 1.8v      | -        | -        | -          |
| Disabled   | Disabled  | Disabled  | Disabled  | Disabled | Disabled | Disabled   |


### Link time optimization / LTO
Link time optimization (LTO for short) have been supported by the IDE since v1.6.11. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep backward compatibility. Enabling LTO in IDE 1.6.10 and older will return an error. 
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!
<br/> <br/>
Here's some numbers to convince you. These sketches were compiled for an **ATmega1284** using **Arduino IDE 1.6.12 (avr-gcc 4.9.2)**. Impressing, right?
<br/>

|                  | Blink.ino  | AnalogReadSerial.ino  | SerialReadWrite.ino | CardInfo.ino |
|------------------|------------|-----------------------|---------------------|--------------|
| **LTO enabled**  | 1084 bytes | 1974 bytes            | 7190 bytes          | 9416 bytes   |
| **LTO disabled** | 1216 bytes | 2414 bytes            | 7710 bytes          | 11518 bytes  |

------

XBee® is a registered trademark of Digi International Inc.


