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
 */
#include <avrio/led.h>
#include "xplbee-demo-adc.h"

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
  gxPLStdIoOpen();
}

// -----------------------------------------------------------------------------
int
iUiTask (gxPLDevice * device) {

  return 0;
}

/* ========================================================================== */
