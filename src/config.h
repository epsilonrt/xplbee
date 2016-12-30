/**
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
#ifndef _CONFIG_H_
#define _CONFIG_H_
#ifdef __cplusplus
extern "C" {
#endif

/* constants ================================================================ */

/* default values =========================================================== */
#define DEFAULT_IO_LAYER                  "xbeezb"
#define DEFAULT_CONNECT_TYPE              gxPLConnectViaHub
#define DEFAULT_HEARTBEAT_INTERVAL        300
#define DEFAULT_CONFIG_HEARTBEAT_INTERVAL 60
#define DEFAULT_HUB_DISCOVERY_INTERVAL    3
#define DEFAULT_ALLOC_STR_GROW            256
#define DEFAULT_LINE_BUFSIZE              256
#define DEFAULT_MAX_DEVICE_GROUP          4
#define DEFAULT_MAX_DEVICE_FILTER         4
#define DEFAULT_XBEE_PORT                 "tty1"
// AVR only, config store in EEPROM
#define DEFAULT_CONFIG_SIZE_MAX           512

/* build options ============================================================ */
#define CONFIG_DEVICE_CONFIGURABLE    1
#define CONFIG_DEVICE_GROUP           1
#define CONFIG_DEVICE_FILTER          1
// add the "remote-addr" field in hbeat.basic
#define CONFIG_HBEAT_BASIC_EXTENSION  1

/* conditionals options ====================================================== */

/* ========================================================================== */
#ifdef __cplusplus
}
#endif
#endif /* _CONFIG_H_ defined */
