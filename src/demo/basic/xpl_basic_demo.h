/*
 * epsirt-pilot.h
 * >>> Describe the contents of your file here
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
#ifndef _P3_PILOT_HEADER_
#define _P3_PILOT_HEADER_
#include <stdlib.h>
#include <gxPL.h>

/* constants ================================================================ */
#define P3_PILOT_VENDOR_ID      "epsirt"
#define P3_PILOT_DEVICE_ID      "sensor"
#define P3_PILOT_INSTANCE_ID    NULL // NULL for auto instance
#define P3_PILOT_DEVICE_VERSION VERSION_SHORT // VERSION_SHORT is automatically defined in version-git.h from git describe
#define P3_PILOT_LOG_LEVEL      LOG_DEBUG
#define IOLAYER_NAME  "xbeezb"
#define IOLAYER_PORT  "tty0"
#define SENSOR_GAP    0.1
#define POLL_RATE_MS  1000

#define SENSOR_NAME "vin"
#define SENSOR_TYPE "voltage"
#define SENSOR_GAP_NAME "gap"

/*
 * AVR_TERMINAL used for gxPL debug purpose only ...
 * AVR has no command line or terminal, constants below allow to setup the
 * the serial port terminal, if NLOG is defined in the makefile,
 * no terminal is used.
 */
#define AVR_TERMINAL_PORT     "tty1"
#define AVR_TERMINAL_BAUDRATE 500000
#define AVR_TERMINAL_FLOW     SERIAL_FLOW_NONE
#include <gxPL/stdio.h>

/* structures =============================================================== */
/* types ==================================================================== */

/* public variables ========================================================= */
extern float fSensorGap;

/* internal public functions ================================================ */
/*
 * User Interface
 */
void vUiInit (void);
int iUiTask (gxPLDevice * device);
/*
 * Sensor Interface
 */
int iSensorInit (gxPLDevice * device);
int iSensorTask (gxPLDevice * device);
  
// !!TODO!! Here you can add more interfaces...

/*
 * xPL Device
 */
gxPLDevice * xDeviceCreate(const char * iolayerport, const char * iolayername, int log);
void vDeviceConfigChanged (gxPLDevice * device, void * udata);
void vDeviceSetConfig (gxPLDevice * device);
/* ========================================================================== */
#endif /* _P3_PILOT_HEADER_ defined */
