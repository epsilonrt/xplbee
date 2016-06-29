/*
 * led_test.c
 * LED Test: Lights the LEDs by a one, then the off one by one and again.
 * 
 * Copyright © 2016 epsilonRT, All rights reserved.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * <http://www.cecill.info>. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#include <avrio/led.h>
#include <avrio/delay.h>

int
main (void) {
  uint8_t ucLed;
  
  vLedInit ();

  for (;;) {

    for (ucLed = 0; ucLed < LED_QUANTITY; ucLed++) {

      vLedSet (xLedGetMask (ucLed));
      delay_ms (250);
    }
    for (ucLed = 0; ucLed < LED_QUANTITY; ucLed++) {

      vLedClear (xLedGetMask (ucLed));
      delay_ms (750);
    }
  }
  return 0;
}
