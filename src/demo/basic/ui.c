/*
 * ui.c
 * >>> User Interface, describe the contents of your file here
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
 *
 * @file
 * @brief
 */
#include <avrio/led.h>
#include <avrio/button.h>
#include "p3-pilot.h"

/* macros =================================================================== */
/* structures =============================================================== */
/* types ==================================================================== */
/* public variables ========================================================= */
/* private variables ======================================================== */
/* private functions ======================================================== */

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
void
vUiInit (void) {
  
  vLedInit();
  vButInit();
  gxPLStdIoOpen();
}

// -----------------------------------------------------------------------------
int
iUiTask (gxPLDevice * device) {
#if 0
  int ret;

  // Sends heartbeat end messages to all devices
  ret = gxPLAppDisableAllDevices (app);
  assert (ret == 0);

  gxPLPrintf ("\nPress any key to close...\n");
  gxPLWait();

  ret = gxPLAppClose (app);
  assert (ret == 0);

  gxPLMessageDelete (message);

  gxPLPrintf ("\neverything was closed.\nHave a nice day !\n");
#endif
  return 0;
}

/* ========================================================================== */
