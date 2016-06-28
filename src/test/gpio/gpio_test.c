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
#include <avrio/assert.h>
#include <avrio/gpio.h>
#include <avrio/delay.h>
#include <avrio/tc.h>
#include <avrio/delay.h>

/* constants ================================================================ */
#define TERMINAL_PORT         "tty0"
#define TERMINAL_BAUDRATE     115200
#define BUTTON_TEST  0

static int utest_count;
#define UTEST_NEW(fmt,...) printf("\nTest %d: "fmt,++utest_count,##__VA_ARGS__)
#define UTEST_SUCCESS() printf ("Success\n")

/* private functions ======================================================== */
#if BUTTON_TEST
// -----------------------------------------------------------------------------
// Callback de changement d'état des boutons
static void
vButtonCB (uGpioMask uPinValues, uint8_t ucBit, eDpEdge edge, void *udata) {
  static uint16_t usCount;
  
  vGpioWrite (LED1, (edge == eEdgeRising) ? true : false);
  printf ("%03d - %c: %u\n", usCount++ % 1000, (edge == eEdgeRising) ? 'P' : 'R', ucBit);
}
#endif

/* main ===================================================================== */
int
main (void) {
  uint8_t i;
  uGpioMask outputs = 0, inputs;

  xSerialIos settings = SERIAL_SETTINGS (TERMINAL_BAUDRATE);
  FILE * tc = xFileOpen (TERMINAL_PORT, O_WR | O_NONBLOCK, &settings);
  stdout = tc;
  stderr = tc;
  sei();
  
  printf ("\n\nGPIO test\n");

  // Test 1: mise à 1 des outputs
  UTEST_NEW ("Set all outputs > ");
  vGpioWriteAll (GPIO_OUTPUTS, true);
  outputs = uGpioReadAll (GPIO_OUTPUTS);
  assert (outputs == GPIO_OUTPUTS);
  UTEST_SUCCESS();

  // Test 2: mise à 0 des outputs
  UTEST_NEW ("Clear all outputs > ");
  vGpioWriteAll (GPIO_OUTPUTS, false);
  outputs = uGpioReadAll (GPIO_OUTPUTS);
  assert (outputs == 0);
  UTEST_SUCCESS();

  // Test 3: basculement des outputs
  UTEST_NEW ("Toggle all outputs to high > ");
  vGpioToggleAll (GPIO_OUTPUTS);
  outputs = uGpioReadAll (GPIO_OUTPUTS);
  assert (outputs == GPIO_OUTPUTS);
  UTEST_SUCCESS();

  UTEST_NEW ("Toggle all outputs to low > ");
  vGpioToggleAll (GPIO_OUTPUTS);
  outputs = uGpioReadAll (GPIO_OUTPUTS);
  assert (outputs == 0);
  UTEST_SUCCESS();

#if BUTTON_TEST
  // Test 4: lecture des boutons poussoirs
  UTEST_NEW ("Reads buttons > ");
  inputs = uGpioReadAll (BUT_MASK);
  assert (inputs == 0);
  UTEST_SUCCESS();

  // Test 5: modif callback
  UTEST_NEW ("Set callback > ");
  vGpioSetCallback (vButtonCB);
  assert (pvGpioCallback() == vButtonCB);
  UTEST_SUCCESS();
#endif
  
  // Test 6: modif udata
  UTEST_NEW ("Set userdata > ");
  vGpioSetUserData (&outputs);
  assert (pvGpioUserData() == &outputs);
  UTEST_SUCCESS();

#if BUTTON_TEST
  // Test 7: Activation des fronts de déclenchement des boutons poussoirs
  UTEST_NEW ("Set active edge for buttons > ");
  for (i = BUT_NAVC; i <= BUT_DBG; i++) {

    vGpioSetPinEdge (i, eEdgeBoth);
    assert (eGpioPinEdge (i) == eEdgeBoth);
  }
  UTEST_SUCCESS();
#endif

  // Tout c'est bien passé
  for (i = 0; i < 15; i++) {

    vGpioToggleAll (GPIO_OUTPUTS);
    delay_ms (200);
  }

#if BUTTON_TEST
  UTEST_NEW ("Polling buttons...\n");
  for (;;) {
    
    // Surveillance des boutons poussoirs
    vGpioPoll();
  }
#else
  printf ("\n\nAll tests (%d) were successful !\n", utest_count);
  for (;;);
#endif
  return 0;
}
/* ========================================================================== */
