/*
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
 *
 * @file
 * @brief
 */
#include <avrio/led.h>
#include <avrio/button.h>
#include <avrio/tc.h>
#include <avrio/delay.h>

/* constants ================================================================ */
#define PORT         "tty1"
#define BAUDRATE     38400

/* main ===================================================================== */
int
main (void) {
  static uint16_t usCount;
  xButMask xCurrent;
  static xButMask xPrevious;

  vLedInit ();
  vButInit ();
  xSerialIos settings = SERIAL_SETTINGS (BAUDRATE);
  FILE * tc = xFileOpen (PORT, O_WR | O_NONBLOCK, &settings);
  stdout = tc;
  sei();
  
  printf ("Button test\n");
  for (;;) {

    xCurrent = xButGet (BUTTON_ALL_BUTTONS);

    if (xCurrent != xPrevious) {

      usCount++;
      xButMask xDiff = xCurrent ^ xPrevious;
      for (uint8_t ucBit = 0; ucBit < BUTTON_QUANTITY; ucBit++) {
        if (xDiff & xButGetMask (ucBit)) {
          
          printf ("%03d - %c: %u\n", usCount % 1000, (xCurrent & xButGetMask (ucBit)) ? 'P' : 'R', ucBit);
        }
      }
      xPrevious = xCurrent;
    }
  }
  return 0;
}
