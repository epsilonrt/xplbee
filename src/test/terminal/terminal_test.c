/*
 * terminal_test.c
 * Serial Terminal Test: Prints 32 times the alphabet and then wait for the 
 * user to transmit characters over the serial link and refers to the receipt 
 * of a carriage return, then resumes. On error, the LED1 flashes quickly, 
 * otherwise it switches to each correct action.
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
#include <avrio/tc.h>
#include <avrio/led.h>
#include <avrio/delay.h>
#include <avr/version.h>

/* constants ================================================================ */
#define PORT         "tty0"
// FXTAL 16 MHz, baudrate max. 2 MBd
#define BAUDRATE     115200
//#define BAUDRATE     250000
//#define BAUDRATE     500000
//#define BAUDRATE     1000000
//#define BAUDRATE     2000000

/* internal public functions ================================================ */
void vAlphabetTest (void);
void vTerminalTest (void);
void vLedAssert (int i);

/* main ===================================================================== */
int
main (void) {

  vLedInit();
  xSerialIos settings = SERIAL_SETTINGS (BAUDRATE);
  settings.flow = SERIAL_FLOW_RTSCTS;
  FILE * tc = xFileOpen (PORT, O_RDWR | O_NONBLOCK, &settings);
  stdout = tc;
  stdin = tc;
  sei();

  for (;;) {

    vAlphabetTest ();
    vTerminalTest ();
  }
  return 0;
}

/* internal public functions ================================================ */
static int iErr;
static int c;

/* -----------------------------------------------------------------------------
 * Prints 32 times the alphabet (A-Z)
 */
void
vAlphabetTest (void) {
  uint8_t ucCount = 32;

  vLedSet (LED_LED1);
  while (ucCount--) {

    c = 'A';
    do {

      iErr = putchar (c);
      vLedAssert (iErr == c);
    }
    while (c++ < 'Z');

    c = '\n';
    iErr = putchar (c);
    vLedAssert (iErr == c);
  }
  vLedClear (LED_LED1);
}

/* -----------------------------------------------------------------------------
 * Wait for the user to transmit characters over the serial link and refers to 
 * the receipt of a carriage return
 */
void
vTerminalTest (void) {
  uint16_t usCount = 0;
  bool isWait = true;

  printf("\nTerminal Test (%s version)\nPress any key (ENTER to quit)...",
            (AVRIO_TC_FLAVOUR == TC_FLAVOUR_POLL) ? "poll" : "irq");
  do {

    c = getchar ();
    if (c != EOF) {

      if (isWait) {
        iErr = putchar ('\n');
        vLedAssert (iErr == '\n');
        isWait = false;
      }
      iErr = putchar (c);
      vLedAssert (iErr == c);
      vLedToggle (LED_LED1);
    }
    else {
      if ( (isWait) && ( (usCount++ % 32768) == 0)) {

        iErr = putchar ('.');
        vLedAssert (iErr == '.');
      }
    }
  }
  while (c != '\r');       /* Return pour terminer */
  iErr = putchar ('\n');
  vLedAssert (iErr == '\n');
}

/* -----------------------------------------------------------------------------
 * Checks that the condition is true, otherwise the LED flashes quickly
 */
void
vLedAssert (int i) {

  if (!i) {

    for (;;) {

      vLedSet (LED_LED1);
      delay_ms (50);
      vLedClear (LED_LED1);
      delay_ms (100);
    }
  }
}

/* ========================================================================== */
