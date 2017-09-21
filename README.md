# Carte xPLBee

*Carte de développement ATMEL avec module XBee®*

---
Copyright © 2015-2017 epsilonRT, All rights reserved.

<a href="http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html">
  <img src="https://raw.githubusercontent.com/epsilonrt/gxPL/master/doc/images/osi.png" alt="osi.png" align="right" valign="top">
</a>

xPLBee est une carte de développement architecturée autour d'un microcontroleur ATMEL (ATMega1284p), elle est compatible avec l'environnement Arduino.

[comment]: # (<img src="https://github.com/epsilonrt/xplbee/raw/master/doc/images/xplbee-board-3d.png" alt="xplbee-board-3d.png" align="center" valign="top">)

![Carte xPLBee](https://github.com/epsilonrt/xplbee/raw/master/doc/images/xplbee-board-3d.png)

Elle est équipée:

* d'un microcontrôleur ATMEGA1284p avec:  
    * 128ko de Flash  
    * 16 ko de RAM  
    * 4 ko d'EEPROM  
    * 2 timers 8 bits et 2 times 16 bits (6 canaux PWM)  
    * 8 voies ADC  
    * 2 USART,  
    * un bus I²C (avec résistances de pull-up déconnectables).  
    * un bus SPI (maître ou esclave)  
    * une interface JTAG (avec connecteur HE10)  
    * un quartz 16MHz  
    * un quartz 32k768 pour le timer RTC  
* d'un support pour module XBee® avec 3 leds, 1 bouton poussoir et 1 connecteur d'extension.  
* d'un connecteur mini USB relié à un circuit FTDI gérant une liaison série. Cette liaison série dispose des signaux TXD/RXD/CTS/RTS/DTR qui peuvent être connectés au microcontrôleur (PD0/PD1/PD4/PD5/RESET), 2 leds signalent les échanges en transmission et réception. Pour l'utilisation d'un bootloader compatible Arduino, les signaux TXD, RXD et DTR sont utilisés. 
* d'une alimentation à découpage acceptant une tension entre 7 et 23V, en l'absence d'une tension externe en entrée, c'est l'alimentation fournie par le connecteur mini USB qui est utilisée (la commutation est automatique). Quelque soit la source de l'alimentation, la tension d'alimentation peut être modifiée: soit 5V, soit 3,3V (position indispensable pour les modules XBee).  
* une led connecté à PB7 (Broche 7 Arduino)  
* un bouton poussoir RESET

L'affectation des broches est la suivante:

![Affectation des broches du microcontrôleur](https://github.com/epsilonrt/xplbee/raw/master/doc/images/atmega1284-pinout.png)

------

XBee® est une marque déposée par Digi International Inc.


