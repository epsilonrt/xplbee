/*
 * sensor.c
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
 */
#include <math.h>
#include <string.h>
#include <avrio/adc.h>
#include "xplbee-demo-adc.h"

/* macros =================================================================== */
/* constants ================================================================ */
/* structures =============================================================== */
/* types ==================================================================== */

/* public variables ========================================================= */
// exceed the gap between current and previous value causes sending message TRIG
float fSensorGap = SENSOR_GAP;

/* private variables ======================================================== */
static gxPLMessage * currentmsg;

/* private functions ======================================================== */
// -----------------------------------------------------------------------------
static int
priSendCurrentValue (gxPLDevice * device, gxPLMessageType msgtype) {
  static float previous = -1.0; // negative to force sending the first measure
  float current;

  // reads ADC5 with averaging over 8 values
  uint16_t usAdc  = usAdcReadAverage (SENSOR_ADC_CHAN, 8);

  // converts the ADC value into physical value (ie voltage...)
  current = ADC_MEASUREMENT (usAdc, SENSOR_ADC_FULLSCALE);

  if (msgtype == gxPLMessageTrigger) {
    /*
     * if trig message requested, check that the gap between the current and
     * previous value is sufficient.
     */
    if (fabs (current - previous) < fSensorGap) {

      // if not, do nothing
      return 0;
    }
  }

  gxPLMessageTypeSet (currentmsg, msgtype);
  gxPLMessagePairSetFormat (currentmsg, "current", "%.2f", current);
  /*
   * if the device is configurable, the instance ID can be
   * changed and should be updated.
   */
  if (gxPLDeviceIsConfigurale (device)) {
    
    gxPLMessageSourceInstanceIdSet (currentmsg, gxPLDeviceInstanceId (device));
  }

  if (msgtype == gxPLMessageTrigger) {

    previous = current;
  }

  // Broadcast the message
  PINFO ("broadcast current value = %.2fV", current);
  return gxPLDeviceMessageSend (device, currentmsg);
}

// -----------------------------------------------------------------------------
static void
prvSensorMessageListener (gxPLDevice * device, gxPLMessage * msg, void * udata) {

  if (gxPLMessagePairExist (msg, "request") == true) {
    // the request key is present in the message

    if (strcmp (gxPLMessagePairGet (msg, "request"), "current") == 0) {

      // this is a request for the current value
      if (gxPLMessagePairExist (msg, "device") == true) {

        if (strcmp (gxPLMessagePairGet (msg, "device"), SENSOR_NAME) != 0) {
          // this request doesn't match to own sensor name
          return;
        }
      }

      if (gxPLMessagePairExist (msg, "type") == true) {

        if (strcmp (gxPLMessagePairGet (msg, "type"), SENSOR_TYPE) != 0) {
          // this request doesn't match to own sensor type
          return;
        }
      }

      // we must send a message to the current value
      priSendCurrentValue (device, gxPLMessageStatus);
    }
  }
}

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
int
iSensorInit (gxPLDevice * device) {
  int ret;

  // Add a responder for sensor.request schema
  ret = gxPLDeviceListenerAdd (device, prvSensorMessageListener,
                               gxPLMessageCommand, "sensor", "request", NULL);
  assert (ret == 0);

  // Create a sensor.basic message conforming to http://xplproject.org.uk/wiki/Schema_-_SENSOR.html
  currentmsg = gxPLDeviceMessageNew (device, gxPLMessageTrigger);
  assert (currentmsg);

  // Setting up the message
  gxPLMessageBroadcastSet (currentmsg, true);
  gxPLMessageSchemaSet (currentmsg, "sensor", "basic");
  gxPLMessagePairAdd (currentmsg, "device", SENSOR_NAME);
  gxPLMessagePairAdd (currentmsg, "type", SENSOR_TYPE);

  // Setting up hardware for the sensor
  vAdcInit();

  return 0;
}

// -----------------------------------------------------------------------------
int
iSensorTask (gxPLDevice * device) {

  return priSendCurrentValue (device, gxPLMessageTrigger);
}

/* ========================================================================== */
